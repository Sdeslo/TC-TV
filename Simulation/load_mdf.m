clear, clc;

%% Select MDF file
[file, path] = uigetfile('*.mdf', 'Select MDF file');
if isequal(file,0)
    error('No file selected');
end

filename = fullfile(path, file);

%% Load MDF
mdfObj = mdf(filename);

%% Get channel list
ch = channelList(mdfObj);

% Adjust group index + channel name based on the file
apps = read(mdfObj, 162, 'ACQ_apps');
sps = read(mdfObj, 157, 'ACQ_sps');
DI1_speed = read(mdfObj, 100, 'DI_Inv1_speed_kmh');
DI2_speed = read(mdfObj, 94, 'DI_Inv2_speed_kmh');
DI3_speed = read(mdfObj, 88, 'DI_Inv3_speed_kmh');
%DI4_speed = read(mdfObj, 82, 'DI_Inv4_speed_kmh');
ax = read(mdfObj, 2, 'RCP_AccelX');
ay = read(mdfObj, 2, 'RCP_AccelY');
yaw = read(mdfObj, 2, 'RCP_yaw');


%% Use one common absolute reference time
tRef = min([ ...
    apps.Time(1), ...
    sps.Time(1), ...
    DI1_speed.Time(1), ...
    DI2_speed.Time(1), ...
    DI3_speed.Time(1), ...
    ax.Time(1), ...
    ay.Time(1), ...
    yaw.Time(1)]);

%% Convert to timeseries
t_apps = seconds(apps.Time - tRef);
ts_apps = timeseries(single(apps.ACQ_apps), t_apps);

t_sps = seconds(sps.Time - tRef);
ts_sps = timeseries(single(sps.ACQ_sps), t_sps);

DI1_raw = abs(single(DI1_speed.DI_Inv1_speed_kmh));
DI2_raw = abs(single(DI2_speed.DI_Inv2_speed_kmh));
DI3_raw = abs(single(DI3_speed.DI_Inv3_speed_kmh));
%DI4_raw = abs(single(DI4_speed.DI_Inv4_speed_kmh));

t_DI1_speed = seconds(DI1_speed.Time - tRef);
ts_DI1_speed = timeseries(DI1_raw, t_DI1_speed);

t_DI2_speed = seconds(DI2_speed.Time - tRef);
ts_DI2_speed = timeseries(DI2_raw, t_DI2_speed);

t_DI3_speed = seconds(DI3_speed.Time - tRef);
ts_DI3_speed = timeseries(DI3_raw, t_DI3_speed);

%t_DI4_speed = seconds(DI4_speed.Time - tRef);
%ts_DI4_speed = timeseries(DI4_raw, t_DI4_speed);

t_ax = seconds(ax.Time - ax.Time(1));
ts_ax = timeseries(single(ax.RCP_AccelX), t_ax);

t_ay = seconds(ay.Time - ay.Time(1));
ts_ay = timeseries(single(ay.RCP_AccelY), t_ay);

t_yaw = seconds(yaw.Time - yaw.Time(1));
ts_yaw = timeseries(single(yaw.RCP_yaw), t_yaw);

% Common start-stop time
t0 = max([ ...
    t_DI1_speed(1), ...
    t_DI2_speed(1), ...
    t_DI3_speed(1)]);

tEnd = min([ ...
    t_apps(end), ...
    t_sps(end), ...
    t_DI1_speed(end), ...
    t_DI2_speed(end), ...
    t_DI3_speed(end), ...
    t_ax(end), ...
    t_ay(end), ...
    t_yaw(end)]);

% Common time vector
Ts = 0.001; % 1 ms
tCommon = (t0:Ts:tEnd)';

apps_vals = interp1(t_apps, single(apps.ACQ_apps), tCommon, 'previous', 'extrap');
ts_apps = timeseries(apps_vals, tCommon - t0);

sps_vals = interp1(t_sps, single(sps.ACQ_sps), tCommon, 'previous', 'extrap');
ts_sps = timeseries(sps_vals, tCommon - t0);

DI1_vals = interp1(t_DI1_speed, DI1_raw, tCommon, 'previous', 'extrap');
DI2_vals = interp1(t_DI2_speed, DI2_raw, tCommon, 'previous', 'extrap');
DI3_vals = interp1(t_DI3_speed, DI3_raw, tCommon, 'previous', 'extrap');
%DI4_vals = interp1(t_DI4_speed, DI4_raw, tCommon, 'previous', 'extrap');

ts_DI1_speed = timeseries(DI1_vals, tCommon - t0);
ts_DI2_speed = timeseries(DI2_vals, tCommon - t0);
ts_DI3_speed = timeseries(DI3_vals, tCommon - t0);
%ts_DI4_speed = timeseries(DI4_vals, tCommon - t0);

ax_vals = interp1(t_ax, single(ax.RCP_AccelX), tCommon, 'linear', 'extrap');
ay_vals = interp1(t_ay, single(ay.RCP_AccelY), tCommon, 'linear', 'extrap');
yaw_vals = interp1(t_yaw, single(yaw.RCP_yaw), tCommon, 'linear', 'extrap');

ts_ax = timeseries(ax_vals, tCommon - t0);
ts_ay = timeseries(ay_vals, tCommon - t0);
ts_yaw = timeseries(yaw_vals, tCommon - t0);