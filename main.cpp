#include <QFile>
#include <QTextStream>
#include "Gauss.h"

int main()
{
	int iCount = 0;
	int iLeft = 0;
	int iRight = 0;
	QList<double> listValue;
	QList<double> listPos;
	{
		bool bIsLeftFound = false;
		QFile file("T2.txt");
		file.open(QFile::ReadOnly);
		QTextStream stream(&file);
		while (!stream.atEnd())
		{
			double v = stream.readLine().trimmed().toDouble();
			if (v != 0)
			{
				if (!bIsLeftFound)
				{
					iLeft = iCount;
					bIsLeftFound = true;
				}
				listValue.push_back(v);
			}
			if (bIsLeftFound && v == 0)
			{
				iRight = iCount-1;
				break;
			}
			iCount++;
		}
		file.close();
	}
	{
		iCount = 0;
		QFile file("T1.txt");
		file.open(QFile::ReadOnly);
		QTextStream stream(&file);
		while (!stream.atEnd())
		{
			double v = stream.readLine().trimmed().toDouble();
			if (iCount >= iLeft && iCount <= iRight)
			{
				listPos.push_back(v);
			}
			iCount++;
		}
		file.close();
	}

	double dXmax;
	double dYmax;
	double dSigma;
	GaussFit(listPos, listValue, dXmax, dYmax, dSigma);
	QList<double> listFitValue;
	GenGaussData(dXmax, dYmax, dSigma, listPos, listFitValue);
	GaussFit(listPos, listFitValue, dXmax, dYmax, dSigma);
}
