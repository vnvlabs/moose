//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ParallelUniqueId.h"
#include "FEProblemBase.h"
#include "ThreadedElementLoopBase.h"

// Forward declarations
class SystemBase;

/**
 * This mutex is used by all derived classes of the ThreadedElementLoop. It
 * is necessary to protect the creation of the strings used in the propagation
 * of the error messages.  It's possible for a thread to have acquired the
 * commonly used mutex in the Threads namespace so this one is here to
 * avoid any deadlocking.
 */
static Threads::spin_mutex threaded_element_mutex;

/**
 * Base class for assembly-like calculations.
 */
template <typename RangeType>
class ThreadedElementLoop : public ThreadedElementLoopBase<RangeType>
{
public:
  ThreadedElementLoop(FEProblemBase & feproblem);

  ThreadedElementLoop(ThreadedElementLoop & x, Threads::split split);

  virtual ~ThreadedElementLoop();

  virtual void caughtMooseException(MooseException & e) override;

  virtual bool keepGoing() override { return !_fe_problem.hasException(); }

  virtual void preElement(const Elem * elem) override;

  virtual void preInternalSide(const Elem * elem, unsigned int side) override;

  virtual void preBoundary(const Elem * elem,
                           unsigned int side,
                           BoundaryID bnd_id,
                           const Elem * lower_d_elem = nullptr) override;

  virtual void neighborSubdomainChanged() override;

protected:
  FEProblemBase & _fe_problem;

  /**
   * Routine to output the ordering of objects within a vector. These objects must implement the
   * name() routine, and it must return a string or compatible type.
   *
   * @tparam RangeType the type of the element-based loop
   * @tparam T the object type
   * @param objs the vector with all the objects (should be pointers)
   * @param objects_type the name of the type of objects. Defaults to the CPP object name
   * @param print_header whether to print a header about the timing of execution and the type of
   * objects
   */
  template <typename T>
  void printExecutionOrdering(const std::vector<T *> objs,
                              const bool print_header = true,
                              const std::string & line_prefix = "[DBG]") const;
};

template <typename RangeType>
ThreadedElementLoop<RangeType>::ThreadedElementLoop(FEProblemBase & fe_problem)
  : ThreadedElementLoopBase<RangeType>(fe_problem.mesh()), _fe_problem(fe_problem)
{
}

template <typename RangeType>
ThreadedElementLoop<RangeType>::ThreadedElementLoop(ThreadedElementLoop & x,
                                                    Threads::split /*split*/)
  : ThreadedElementLoopBase<RangeType>(x), _fe_problem(x._fe_problem)
{
}

template <typename RangeType>
ThreadedElementLoop<RangeType>::~ThreadedElementLoop()
{
}

template <typename RangeType>
void
ThreadedElementLoop<RangeType>::caughtMooseException(MooseException & e)
{
  Threads::spin_mutex::scoped_lock lock(threaded_element_mutex);

  std::string what(e.what());
  _fe_problem.setException(what);
}

template <typename RangeType>
void
ThreadedElementLoop<RangeType>::preElement(const Elem * el)
{
  _fe_problem.setCurrentSubdomainID(el, ThreadedElementLoopBase<RangeType>::_tid);
}

template <typename RangeType>
void
ThreadedElementLoop<RangeType>::preInternalSide(const Elem * el, unsigned int side)
{
  _fe_problem.setNeighborSubdomainID(el, side, ThreadedElementLoopBase<RangeType>::_tid);
}

template <typename RangeType>
void
ThreadedElementLoop<RangeType>::preBoundary(const Elem * /*elem*/,
                                            unsigned int /*side*/,
                                            BoundaryID bnd_id,
                                            const Elem * /*=nullptr*/)
{
  _fe_problem.setCurrentBoundaryID(bnd_id, ThreadedElementLoopBase<RangeType>::_tid);
}

template <typename RangeType>
void
ThreadedElementLoop<RangeType>::neighborSubdomainChanged()
{
  _fe_problem.neighborSubdomainSetup(ThreadedElementLoopBase<RangeType>::_neighbor_subdomain,
                                     ThreadedElementLoopBase<RangeType>::_tid);
}

template <typename RangeType>
template <typename T>
void
ThreadedElementLoop<RangeType>::printExecutionOrdering(const std::vector<T *> objs,
                                                       const bool print_header,
                                                       const std::string & line_prefix) const
{
  if (objs.size())
  {
    auto console = _fe_problem.console();
    auto objects_type = MooseUtils::prettyCppType(objs[0]);
    std::vector<MooseObject *> moose_objs;
    for (auto obj_ptr : objs)
      moose_objs.push_back(dynamic_cast<MooseObject *>(obj_ptr));
    auto names = ConsoleUtils::mooseObjectVectorToString(moose_objs);

    // Print string with a DBG prefix and with sufficient line breaks
    std::string message = print_header ? "Executing " + objects_type + " on " +
                                             _fe_problem.getCurrentExecuteOnFlag().name() + "\n"
                                       : "";
    message += (print_header ? "Order of execution:\n" : "") + names;
    console << ConsoleUtils::formatString(message, line_prefix) << std::endl;
  }
}
