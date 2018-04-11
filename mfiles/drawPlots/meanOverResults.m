
clear;
clc;

%%
sum_FUE_IL = [];
C_FUE_Mat_IL = cell(1,16);
P_FUE_Mat_IL = cell(1,16);
for i=1:16
    fprintf('FBS num = %d\t', i);
    sumfue = 0.;
    c_fue_vec = zeros(1,i);
    p_fue_vec = zeros(1,i);
    Cnt = 0;
    
    for j=1:100
        s = sprintf('DATA/April9/R_4_1.5_IL/pro_32_%d_%d.mat',i,j);
        filename = strcat(s);
        if exist(s)
            load(filename);
            sumfue = sumfue + QFinal.sum_CFUE;
            c_fue_vec = c_fue_vec + QFinal.C_FUE;
            pp = zeros(1,i);
            for kk = 1:i
                pp(1,kk) = QFinal.FBS{kk}.P;
            end
            p_fue_vec = p_fue_vec + pp;
            Cnt = Cnt+1;
        end
    end
    fprintf('Total Cnt = %d\n',Cnt);
    sum_FUE_IL = [sum_FUE_IL sumfue/Cnt];
    C_FUE_Mat_IL{i} = c_fue_vec./Cnt;
    P_FUE_Mat_IL{i} = p_fue_vec./Cnt;
end
%%
sum_FUE_CL = [];
C_FUE_Mat_CL = cell(1,16);
P_FUE_Mat_CL = cell(1,16);
for i=1:16
    fprintf('FBS num = %d\t', i);
    sumfue = 0.;
    c_fue_vec = zeros(1,i);
    p_fue_vec = zeros(1,i);
    Cnt = 0;
    
    for j=1:100
        s = sprintf('DATA/Jan22/R_4_CL/pro_32_%d_%d.mat',i,j);
        filename = strcat(s);
        if exist(s)
            load(filename);
            sumfue = sumfue + QFinal.sum_CFUE;
            c_fue_vec = c_fue_vec + QFinal.C_FUE;
            pp = zeros(1,i);
            for kk = 1:i
                pp(1,kk) = QFinal.FBS{kk}.P;
            end
            p_fue_vec = p_fue_vec + pp;
            Cnt = Cnt+1;
        end
    end
    fprintf('Total Cnt = %d\n',Cnt);
    sum_FUE_CL = [sum_FUE_CL sumfue/Cnt];
    C_FUE_Mat_CL{i} = c_fue_vec./Cnt;
    P_FUE_Mat_CL{i} = p_fue_vec./Cnt;
end
%%
sum_FUE_spon = [];
C_FUE_Mat_spon = cell(1,16);
for i=1:16
    fprintf('FBS num = %d\t', i);
    sumfue = 0.;
    c_fue_vec = zeros(1,i);
    Cnt = 0;
    
    for j=1:100
        s = sprintf('DATA/Apr10/spon/pro_32_%d_%d.mat',i,j);
        filename = strcat(s);
        if exist(s)
            load(filename);
            sumfue = sumfue + QFinal.sum_CFUE;
            c_fue_vec = c_fue_vec + QFinal.C_FUE;
            Cnt = Cnt+1;
        end
    end
    fprintf('Total Cnt = %d\n',Cnt);
    sum_FUE_spon = [sum_FUE_spon sumfue/Cnt];
    C_FUE_Mat_spon{i} = c_fue_vec./Cnt;
end
%%
figure;
hold on;
grid on;
box on;
% plot( ones(1,14)*1.5, '--b', 'LineWidth',1);
for i=2:14
    vec = P_FUE_Mat_IL{i};
    for j=1:size(vec,2)
        plot(i,vec(j), 'sr', 'LineWidth',1.5,'MarkerSize',10, 'MarkerFaceColor','r', 'MarkerEdgeColor','b');
    end
end
% plot(min_FUE, '--r', 'LineWidth',1,'MarkerSize',10);
% plot(min_FUE_ref, '--b', 'LineWidth',1,'MarkerSize',10);
% title('Capacity of all members of a cluster','FontSize',14, 'FontWeight','bold');
xlabel('Cluster size','FontSize',14, 'FontWeight','bold');
% ylabel('Capacity(b/s/Hz)','FontSize',14, 'FontWeight','bold');
ylabel('Power(dBm)','FontSize',14, 'FontWeight','bold');
xlim([2 14]);
% ylim([0 20]);
% legend({'\textbf{required QoS ($log_2(q_k)$)}','\textbf{CDP-Q/IL}'},'FontSize',14, 'Interpreter','latex');
%%
figure;
hold on;
grid on;
box on;
plot( ones(1,14)*1.5, '--b', 'LineWidth',1);
for i=2:14
    vec = C_FUE_Mat_CL{i};
    for j=1:size(vec,2)
        plot(i,vec(j), 'sr', 'LineWidth',1.5,'MarkerSize',10, 'MarkerFaceColor','r', 'MarkerEdgeColor','b');
    end
end
% plot(min_FUE, '--r', 'LineWidth',1,'MarkerSize',10);
% plot(min_FUE_ref, '--b', 'LineWidth',1,'MarkerSize',10);
% title('Capacity of all members of a cluster CL','FontSize',14, 'FontWeight','bold');
xlabel('Cluster size','FontSize',14, 'FontWeight','bold');
ylabel('Capacity(b/s/Hz)','FontSize',14, 'FontWeight','bold');
% ylabel('Power(dBm)','FontSize',14, 'FontWeight','bold');
xlim([2 14]);
% ylim([0 20]);
% legend({'\textbf{required QoS ($log_2(q_k)$)}','\textbf{CDP-Q/CL}'},'FontSize',14, 'Interpreter','latex');
%%
figure;
hold on;
grid on;
box on;
plot( ones(1,14)*1.5, '--b', 'LineWidth',1);
for i=2:14
    vec = C_FUE_Mat_spon{i};
    for j=1:size(vec,2)
        plot(i,vec(j), 'sr', 'LineWidth',1.5,'MarkerSize',10, 'MarkerFaceColor','r', 'MarkerEdgeColor','b');
    end
end
% plot(min_FUE, '--r', 'LineWidth',1,'MarkerSize',10);
% plot(min_FUE_ref, '--b', 'LineWidth',1,'MarkerSize',10);
% title('Capacity of all members of a cluster spon','FontSize',14, 'FontWeight','bold');
xlabel('Cluster size','FontSize',14, 'FontWeight','bold');
ylabel('Capacity(b/s/Hz)','FontSize',14, 'FontWeight','bold');
xlim([2 14]);
ylim([0 20]);
legend({'\textbf{required QoS ($log_2(q_k)$)}','\textbf{Simultaneous}'},'FontSize',14, 'Interpreter','latex');
%%
figure;
hold on;
grid on;
box on;
% plot( ones(1,16)*2.0, '--k', 'LineWidth',1 );
plot(sum_FUE_IL, '--sr', 'LineWidth',1.5,'MarkerSize',10, 'MarkerFaceColor','r', 'MarkerEdgeColor','b');
plot(sum_FUE_CL, '--dg', 'LineWidth',1,'MarkerSize',10);
% plot(sum_FUE_spon, '--*b', 'LineWidth',1,'MarkerSize',10);
% title('SUM capacity of cluster members','FontSize',14, 'FontWeight','bold');
xlabel('Cluster size','FontSize',14, 'FontWeight','bold');
ylabel('Capacity(b/s/Hz)','FontSize',14, 'FontWeight','bold');
xlim([2 14]);
ylim([0 90]);
legend({'CDP-Q/IL','CDP-Q/CL'},'FontSize',14, 'FontWeight','bold');
