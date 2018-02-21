
lambda = @(x) 300*(x(:,1).^2 + x(:,2).^2);
lamstar = 120;
N=poissrnd(lamstar); x = rand(N,2)-0.5; % homogeneous PP
ind = find(rand(N,1) < lambda(x)/lamstar);
xa = x(ind,:); % thinned PP

sel = xa;

figure;
plot(1000*sel(:,1),1000*sel(:,2), '^k');
hold on;

s = 1000; % scale factor
edges = zeros(1,size(sel,1));
for i=1:size(sel,1)
    cnt = 0;
    for j=1:size(sel,1)
        if i~=j
            dist = (sel(i,1)-sel(j,1))^2 + (sel(i,2)-sel(j,2))^2;
            if dist <= 0.1^2
                plot([s*sel(i,1) s*sel(j,1)], [s*sel(i,2) s*sel(j,2)]);
                cnt = cnt + 1;
            end
        end
    end
    edges(1,i) = cnt;
end


grid on;
box on;
% xlim([-500 500]);
% ylim([-500 500]);
% title('Eselample of mmWave BSs distribution','FontSize',14, 'FontWeight','bold');
xlabel('x-axis','FontSize',14, 'FontWeight','bold');
ylabel('y-axis','FontSize',14, 'FontWeight','bold');

figure;
bar(edges);

figure;
histogram(edges);
grid on;