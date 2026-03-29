function repoRoot = find_repo_root_Sim(modelDir)
% modelDir is the folder that contains the model ( ...\vcu-firmware\VCU-firmware )

[parent, name] = fileparts(modelDir);

if ~strcmp(name,'VCU-firmware')
    error("Expected model directory to be 'Simulation' but got '%s'", name);
end

repoRoot = parent;  % ...\vcu-firmware
end

