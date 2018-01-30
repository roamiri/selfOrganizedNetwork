function makePDF(file)
    input = strcat( file, '.fig');
    h = open(input);
    ax = gca;
    ax.FontWeight = 'bold';
    ax.FontSize = 16;
    set(h,'Units','Inches');
    pos = get(h,'Position');
    set(h,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)]);
    output = strcat(file,'.pdf');
    print(h,output,'-dpdf','-r0');
    close;
end

