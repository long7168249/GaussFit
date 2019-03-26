#pragma once

void GaussFit(QList<double> &listPos, QList<double> listValue, double &dXmax, double &dYmax, double &dSigma);
void GenGaussData(double dXmax, double dYmax, double dSigma, QList<double> &listPos, QList<double> &listValue);
