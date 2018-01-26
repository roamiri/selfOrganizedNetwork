function R = R_9(C, q)
    
    if (C<4*q)
        R = -cos((C*pi)/(2*q));
    else
        R = -1;
    end

%             R = beta*fbs.C_FUE*(mue(1).C).^2 -(fbs.C_FUE-q_fue).^2 - (1/beta)*dum1;
%              R = fbs.C_FUE - abs(fbs.C_FUE-q_fue);
%             if (fbs.C_FUE < 4*q_fue)
% %                 xxx = (pi/(2*q_fue));
%                 R = (q_fue - abs(fbs.C_FUE -2*q_fue))/(q_fue); %R = min(tan(xxx*fbs.C_FUE), 1000);
%             else
% %                 xxx = -(pi/(2*q_fue));
%                 R = -1;%R = max(tan(xxx*fbs.C_FUE), -1000);
%             end