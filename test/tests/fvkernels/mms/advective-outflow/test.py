import mms
import unittest
from mooseutils import fuzzyAbsoluteEqual

class TestOutflow(unittest.TestCase):
    def test(self):
        df1 = mms.run_spatial('advection-outflow.i', 7, y_pp=['L2u', 'L2v'])
        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1,
                 label=['L2u', 'L2v'],
                 marker='o',
                 markersize=8,
                 num_fitted_points=3,
                 slope_precision=1)
        fig.save('outflow.png')
        for label,value in fig.label_to_slope.items():
            if label == 'L2u':
                self.assertTrue(fuzzyAbsoluteEqual(value, 1., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class TestExtrapolation(unittest.TestCase):
    def test(self):
        df1 = mms.run_spatial('advection.i', 7, y_pp=['L2u', 'L2v'])
        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1,
                 label=['L2u', 'L2v'],
                 marker='o',
                 markersize=8,
                 num_fitted_points=3,
                 slope_precision=1)
        fig.save('extrapolation.png')
        for label,value in fig.label_to_slope.items():
            if label == 'L2u':
                self.assertTrue(fuzzyAbsoluteEqual(value, 1., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))
