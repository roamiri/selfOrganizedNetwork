clear;

d = 30:10:200;

mu = 0.0;
sigma = 8.7;
NumRealization = 1e1;
X = sigma * randn(size(d,2), NumRealization);

for i=1:size(d,2)
%     for j=1:4
        Y(i)=(sum(X(i,:))/NumRealization);
%     end
end


alpha = 72.0;
beta = 2.92;
d = 30:10:200;
sigma2 = 10^0.87;
% X = sigma2 * randn(1,size(d,2));
PL1 = alpha + beta * 10 * log10(d) + Y;
PL2 = 62.3+32*log10(d/5);
semilogx(d,PL1,'sr');
hold on;
semilogx(d,PL2,'-b');
% xlim([30 200]);
grid on;