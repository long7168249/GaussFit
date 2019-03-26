#include <Dense>
#include <QList>
#include <QtMath>
using namespace Eigen;
using namespace std;

void GaussFit(QList<double> &listPos, QList<double> listValue, double &dXmax, double &dYmax, double &dSigma)
{
	int iSize = listPos.size();

	VectorXd z(iSize);
	for (int i=0; i<iSize; ++i)
	{
		double v = listValue[i];
		z(i) = qLn(v);
	}

	MatrixXd x = MatrixXd::Constant(iSize, 3, 1);
	for (int i=0; i<iSize; ++i)
	{
		x(i, 1) = listPos[i];
		x(i, 2) = listPos[i]*listPos[i];
	}

	VectorXd b(3);
	b = ((x.transpose()*x).inverse())*x.transpose()*z;

	double s = -1/b(2);
	dXmax = b(1)*s/2;
	double lny = b(0) + dXmax*dXmax/s;
	dYmax = qExp(lny);
	dSigma = qSqrt(s/2);
}

void GenGaussData(double dXmax, double dYmax, double dSigma, QList<double> &listPos, QList<double> &listValue)
{
	listValue.clear();
	int iSize = listPos.size();
	for (int i=0; i<iSize; ++i)
	{
		double dPos = listPos[i];
		listValue.push_back(dYmax*qExp(-qPow(dPos - dXmax, 2)/(2*qPow(dSigma, 2))));
	}
}
