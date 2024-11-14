%{
    EnergyTrace MATLAB plot for LPM0 and LPM3 transitions

    
Import files lpm0.csv and lpm3.csv
Plot Energy (mJ) vs Time (s) and Power (mW) vs Time (s) as subplots
Convert values from:
time (ns) to time (s)
energy (nJ) to energy (mJ)
%}

% Clear workspace and close all figures
clc; close all;

% % Load data from CSV files
% lpm0_data = readtable('lpm0.csv');
% lpm3_data = readtable('lpm3.csv');

% Convert units
time_lpm0 = lpm0.Timeulong * 1e-9; % Convert from ns to s
energy_lpm0 = lpm0.Energyfloat * 1e-3; % Convert from uJ to mJ
power_lpm0 = lpm0.Powerfloat; % Already in mW

time_lpm3 = lpm3.Timeulong * 1e-9; % Convert from ns to s
energy_lpm3 = lpm3.Energyfloat * 1e-3; % Convert from uJ to mJ
power_lpm3 = lpm3.Powerfloat; % Already in mW

% Create figure and plot Energy vs Time
figure;

% Subplot for Energy vs Time
subplot(2,1,1);
plot(time_lpm0, energy_lpm0, 'b', 'LineWidth', 1.5); % LPM0 in blue
hold on;
plot(time_lpm3, energy_lpm3, 'r', 'LineWidth', 1.5); % LPM3 in red
title('Energy vs Time');
xlabel('Time (s)');
ylabel('Energy (mJ)');
legend('LPM0', 'LPM3');
grid on;
hold off;

% Subplot for Power vs Time
subplot(2,1,2);
plot(time_lpm0, power_lpm0, 'b', 'LineWidth', 1.5); % LPM0 in blue
hold on;
plot(time_lpm3, power_lpm3, 'r', 'LineWidth', 1.5); % LPM3 in red
title('Power vs Time');
xlabel('Time (s)');
ylabel('Power (mW)');
legend('LPM0', 'LPM3');
grid on;
box on;
hold off;

% Set figure background to white
set(gcf, 'Color', 'w');