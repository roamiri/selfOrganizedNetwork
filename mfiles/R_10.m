function R = R_10(C, q)
    
    if(C<4*q)
        R = -cos(pi*C/q);
    else
        R = -1;
    end
end