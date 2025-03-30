sDataDefFile = ''; %Empty -> Data Generated into Model source file

%% Signal driver_up
driver_up = Simulink.Signal;
driver_up.DataType = 'boolean';
driver_up.Min = 0;
driver_up.Max = 1;
driver_up.CoderInfo.StorageClass = 'Custom';
driver_up.CoderInfo.CustomStorageClass = 'ExportToFile';
driver_up.CoderInfo.CustomAttributes.DefinitionFile = sDataDefFile; 

%% Parameter auto_up_time
auto_up_time            = Simulink.Parameter;
auto_up_time.Value      = 100;
auto_up_time.DataType   = 'uint8';
auto_up_time.Min        = 0;
auto_up_time.Max        = 255;
auto_up_time.CoderInfo.StorageClass = 'Custom';
auto_up_time.CoderInfo.CustomStorageClass = 'ConstVolatile';
auto_up_time.CoderInfo.CustomAttributes.DefinitionFile = sDataDefFile; 

%% Signal driver_down
driver_down                 = copy(driver_up);

%% Signal passenger_up
passenger_up                = copy(driver_up);

%% Signal passenger_down
passenger_down              = copy(driver_up);
move_up                     = copy(driver_up);
move_down                   = copy(driver_up);
obstacle_detection          = copy(driver_up);
driver_validated_neutral    = copy(driver_up);
driver_validated_up         = copy(driver_up);
driver_validated_down       = copy(driver_up);
passenger_validated_neutral = copy(driver_up);    
passenger_validated_up      = copy(driver_up);    
passenger_validated_down    = copy(driver_up);    
endstop_top                 = copy(driver_up);    
endstop_bottom              = copy(driver_up);
prev_move_up                = copy(driver_up);

obstacle_position = Simulink.Signal;
obstacle_position.DataType = 'fixdt(0,16,0.001,0)';
obstacle_position.Min = 0;
obstacle_position.Max = 0.45;
obstacle_position.CoderInfo.StorageClass        = 'Custom';
obstacle_position.CoderInfo.CustomStorageClass  = 'ExportToFile';
obstacle_position.CoderInfo.CustomAttributes.DefinitionFile = sDataDefFile; 
 
window_position = copy(obstacle_position);
  
%% Parameters (Global Const Volatile)
position_endstop_top            = Simulink.Parameter;
position_endstop_top.Value      = 0.4;    
position_endstop_top.DataType   = 'fixdt(0,16,0.001,0)';
position_endstop_top.Min        = 0.35;
position_endstop_top.Max        = 0.45;
position_endstop_top.CoderInfo.StorageClass = 'Custom';
position_endstop_top.CoderInfo.CustomStorageClass = 'ConstVolatile';
position_endstop_top.CoderInfo.CustomAttributes.DefinitionFile = sDataDefFile; 

auto_down_time = copy(auto_up_time);
emergency_down_time = copy(auto_up_time);

%% Constant
bFALSE            = Simulink.Parameter;
bFALSE.Value      = 0;
bFALSE.DataType   = 'boolean';
bFALSE.Min        = 0;
bFALSE.Max        = 1;
bFALSE.CoderInfo.StorageClass = 'Custom';
bFALSE.CoderInfo.CustomStorageClass = 'Define';
