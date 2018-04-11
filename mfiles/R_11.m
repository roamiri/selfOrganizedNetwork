function R = R_11(C, q)
    g = log2(1+q);
    R = exp(-(C - g)^2);
end