#ifndef BM_HPP
#define BM_HPP

class BisectionMethod
{
    double a, b, delta; // private
public:
    BisectionMethod(double);
    void NewtonRaphson();
    void FixedPoint();

    void find_interval();
    void get_interval(double, double);
    double f(double);
    void bisection();
    ~BisectionMethod();
};

#endif