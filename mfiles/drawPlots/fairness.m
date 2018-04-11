
clear;
clc;
%%
s = sprintf('oct10/FUE_R_18_time.mat');
filename = strcat(s);
load(filename);

s = sprintf('oct10/FUE_Rref_noshare.mat');
filename = strcat(s);
load(filename);

%%
figure;
hold on;
grid on;
box on;

fariness_IL = zeros(1,16);
fariness_CL = zeros(1,16);
fariness_spon = zeros(1,16);

for i=1:16
vec_IL = C_FUE_Mat_IL{i};
vec_CL = C_FUE_Mat_CL{i};
vec_spon = C_FUE_Mat_spon{i};
num_IL = 0.0;
num_CL = 0.0;
num_spon = 0.0;
denom_IL = 0.0;
denom_CL = 0.0;
denom_spon = 0.0;
n = size(vec_IL,2);
for j=1:n
    num_IL = num_IL + vec_IL(j);
    num_CL = num_CL + vec_CL(j);
    num_spon = num_spon + vec_spon(j);
    denom_IL = denom_IL + vec_IL(j)^2;
    denom_CL = denom_CL + vec_CL(j)^2;
    denom_spon = denom_spon + vec_spon(j)^2;
end
    fariness_IL(i) = (num_IL^2)/(n*denom_IL);
    fariness_CL(i) = (num_CL^2)/(n*denom_CL);
    fariness_spon(i) = (num_spon^2)/(n*denom_spon);
end
plot(fariness_IL, '--sr', 'LineWidth',1.5,'MarkerSize',10, 'MarkerFaceColor','r', 'MarkerEdgeColor','b');
plot(fariness_CL,  '--dg', 'LineWidth',1,'MarkerSize',10);
% plot(fariness_spon, 'b--.', 'LineWidth',1,'MarkerSize',10);

xlim([2 14]);
ylim([0.8 1.1]);
% title('Fairness index','FontSize',14, 'FontWeight','bold');
xlabel('Cluster size','FontSize',14, 'FontWeight','bold');
ylabel('Jain''s Index For Fairness','FontSize',14, 'FontWeight','bold');
legend({'CDP-Q/IL','CDP-Q/CL'},'FontSize',14, 'FontWeight','bold');
