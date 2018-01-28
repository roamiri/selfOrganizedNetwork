
clear;
clc;
close all;
filename = '../build/clusters.csv';
clusters = csvread(filename);
%%
num_cluster = size(clusters, 1);
max_num_members = size(clusters, 2);
figure;
hold on;
for i=1:num_cluster-2
    color = rand(1,3);
%     color = [0,0,0];
    plot(clusters(i,1),clusters(i,2), '^', 'MarkerFaceColor',color,'MarkerEdgeColor',color, 'MarkerSize', 14, 'linewidth', 2);
    for j=3:2:max_num_members
        if(isnan(clusters(i,j))==0 && clusters(i,j)~=0.0)
            plot(clusters(i,j),clusters(i,j+1), '^', 'color', color, 'MarkerSize', 10, 'linewidth', 2);
        end
    end
end

grid on;
box on;
xlim([-500 500]);
ylim([-500 500]);
% title('Example of mmWave BSs distribution','FontSize',14, 'FontWeight','bold');
xlabel('x','FontSize',14, 'FontWeight','bold');
ylabel('y','FontSize',14, 'FontWeight','bold');
% legend({'mmWave BS'},'FontSize',14, 'FontWeight','bold');
%%
% savefig('cluster_model2.fig')
h = open('DATA/cluster4/cluster4.fig');
ax = gca;
ax.FontWeight = 'bold';
ax.FontSize = 24;
% ax.XLabel='X';
% ax.YLabel='Y';
set(h,'Units','Inches');
pos = get(h,'Position');
set(h,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)])
print(h,'DATA/cluster4/cluster4.pdf','-dpdf','-r0');
