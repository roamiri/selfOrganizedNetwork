%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Simulation of Power Allocation in dense mmWave network using 
%   Spontaneous power allocation
%   All BSs use maximum power
%
function FBS_out = PA_Spon(Npower, fbsCount,femtocellPermutation, NumRealization, saveNum, CL)

%% Initialization
clc;
total = tic;
%% Parameters
Pmin = -10;                                                                                                                                                                                                                                                                                                                                                                           %dBm
Pmax = 35; %dBm

%sinr_th = 1.64;%10^(2/10); % I am not sure if it is 2 or 20!!!!!
%gamma_th = log2(1+sinr_th);

%% Minimum Rate Requirements for N users
q_fue = 2.83; q_mue = 2.83;
%% Q-Learning variables
% Actios
actions = linspace(Pmin, Pmax, Npower);

%% Generate the UEs
mue(1) = UE(204, 207);
MBS = BaseStation(0 , 0 , 50);
%%
%Generate fbsCount=16 FBSs, FemtoStation is the agent of RL algorithm
FBS_Max = cell(1,16);
for i=1:3
%     if i<= fbsCount
        FBS_Max{i} = mmWaveBS(180+(i-1)*35,150, MBS, mue, 10);
%     end
end

for i=1:3
%     if i+3<= fbsCount
        FBS_Max{i+3} = mmWaveBS(165+(i-1)*30,180, MBS, mue, 10);
%     end
end

for i=1:4
%     if i+6<= fbsCount
        FBS_Max{i+6} = mmWaveBS(150+(i-1)*35,200, MBS, mue, 10);
%     end
end

for i=1:3
%     if i+10<= fbsCount
        FBS_Max{i+10} = mmWaveBS(160+(i-1)*35,240, MBS, mue, 10);
%     end
end

for i=1:3
%     if i+13<= fbsCount
        FBS_Max{i+13} = mmWaveBS(150+(i-1)*35,280, MBS, mue, 10);
%     end
end
%%
% 
FBS = cell(1,fbsCount);

for i=1:fbsCount
    FBS{i} = FBS_Max{femtocellPermutation(i)};
end

%% Calc channel coefficients
    fbsNum = size(FBS,2);
    G = zeros(fbsNum+1, fbsNum+1); % Matrix Containing small scale fading coefficients
    L = zeros(fbsNum+1, fbsNum+1); % Matrix Containing large scale fading coefficients
    [G, L] = measure_channel(FBS,MBS,mue,NumRealization);
    %% Main Loop
%     fprintf('Loop for %d number of FBS :\t', fbsCount);
%      textprogressbar(sprintf('calculating outputs:'));
    
    for j=1:size(FBS,2)
        fbs = FBS{j};
        fbs.P = Pmax;
        FBS{j} = fbs;
    end
    
    SINR_UE_Vec = SINR_UE(G, L, FBS, MBS, -120);
    
    for j=1:size(FBS,2)
        fbs = FBS{j};
        fbs.C_FUE = log2(1+SINR_UE_Vec(j));
        FBS{j}=fbs;
    end
    
    answer.FBS = FBS;
    for j=1:size(FBS,2)
        c_fue(1,j) = FBS{1,j}.C_FUE;
    end
    sum_CFUE = 0.0;
    for i=1:size(FBS,2)
        sum_CFUE = sum_CFUE + FBS{i}.C_FUE;
    end
    answer.C_FUE = c_fue;
    answer.sum_CFUE = sum_CFUE;
    answer.q = q_fue;
    QFinal = answer;
    save(sprintf('DATA/Apr10/spon/pro_%d_%d_%d.mat',Npower, fbsCount, saveNum),'QFinal');
    FBS_out = FBS;
end
