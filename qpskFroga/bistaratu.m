M = csvread('csvFitx.csv');
t = csvread('times.csv');
B = M';
B = B(:)';
C = t';
C = C(:)';

figure(1);
plot(C,B);
title('xxxxxxx Bitstreama QPSKn modulatuta');
xlabel('t(s)');
