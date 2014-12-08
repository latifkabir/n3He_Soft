function B = cal_field(M,Rp,M0,S)
% CAL_FIELD  Use the calibrations of FIT_SYM to calcualte the symmetry
%       axis components of the B-field from measured voltages
%
%  M     is an n*3 matrix of measured voltages from the 3-axis probe,
%        for n independent measurements
%  Rp	 is the 3*3 calibrated inverse response matrix from FIT_SYM
%  M0	 is the 1*3 vector of voltage offsets, one for each axis from FIT_SYM
%  S     is an optional n*10 symmetry matrix, 
%
%  B	 is the n*3 matrix of n magnetic fields vectors

% 2014-10-08  Chrisotpher Crawford <crawford@pa.uky.edu>

Q=[ sqrt(2),0,0; 0,1,1; 0,-1,1 ]/sqrt(2);
for i=1:size(M,1)
    if nargin<4, 
        B(i,:) = (M(i,:)-M0) * Rp';
    else
        Sa = reshape(S(i,1:9),3,3);
        B(i,:) = (M(i,:) - M0) * Rp' * Q * Sa' * Q';
    end
end