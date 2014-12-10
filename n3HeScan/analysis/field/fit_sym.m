function [B,Rp,M0] = fit_sym(M,S,B0)
% [B,Rp,M0] = fit_sym(M,S,B0)
%    Fit the calibration of a 3-d magnetic field probe from
%    voltages measured under different symmetries of the probe.
%
%  M     is the n*3 matrix of measured voltages from the 3-axis probe
%          under each of the n symmetry orientations of the probe
%  S	 is the n*10 matrix of symmetry transformations for each orientation
%          The first 9 entries in a row are the 9 elements of the symmetry
%	       rotation matrix.  The last entry in the row is always 1
%  B0	 is the scalar magnitude of the magnetic field during the calibration
%          default value: average magnitude of all entries
%
%  Rp	 is the 3*3 calibrated inverse response matrix
%  M0	 is the 1*3 vector of voltage offsets, one for each axis
%  B	 is the 1*3 magnetic field vector, of magnitude B0
%
% 2014-10-08  Christopher Crawford <crawford@pa.uky.edu>

T=pinv(S)*M;
M0=T(10,:);

Tp=[ T(1:3,:)'; T(4:6,:)'; T(7:9,:)' ];
[Rh,L,Bh]=svd(Tp);

if nargin<3, B0=mean(sqrt(diag(M*M'))); end
R=[ Rh(1:3,1), Rh(4:6,1), Rh(7:9,1) ] * L(1,1)/B0;
Q=[ sqrt(2),0,0; 0,1,1; 0,-1,1 ]/sqrt(2);
Rp=Q*pinv(R);
B=(Q*Bh(:,1))'*B0;

% diagnostics
if 1
    disp('symmetry eigenvalues:'); [U,W,V]=svd(S); disp(diag(W)');
    disp('eigenvalues of T=RB:'); disp(diag(L)');
    disp('linear residuals:'); disp(M-S*T);
    disp('full residuals:');
    Ts=Rh(:,1)*L(1,1)*Bh(:,1)';
    Tf=[ Ts(1:3,:)'; Ts(4:6,:)'; Ts(7:9,:)'; M0 ];
    disp(M-S*Tf);
    disp('field residuals:');
    disp(cal_field(M,Rp,M0,S) - ones(size(M,1),1)*B);
end
