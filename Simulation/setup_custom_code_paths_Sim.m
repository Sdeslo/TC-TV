function setup_custom_code_paths_Sim(modelName)

if nargin < 1
    modelName = bdroot;
end

% Make sure the model is open + saved so FileName exists
modelFile = get_param(modelName,'FileName');
if isempty(modelFile)
    error("Model file path is empty. Save the model once, then retry.");
end
modelDir = fileparts(modelFile);

% Repo root = parent of the folder named "VCU-firmware" 
repoRoot = find_repo_root_Sim(modelDir);

% Paths (portable) 
incDirs = {
    fullfile(repoRoot, 'C_code')
};

srcFiles = {
    'TV.c'
};

hdrFiles = {
    'TV.h'
};

% Join helper 
joinList = @(c) strjoin(c, newline);

% Set SIMULATION TARGET custom code (ConfigSet)
cs = getActiveConfigSet(modelName);

set_param(cs, 'SimUserIncludeDirs',  joinList(incDirs));     % include dirs
set_param(cs, 'SimUserSources',      joinList(srcFiles));    % source files
set_param(cs, 'SimCustomHeaderCode', joinList(hdrFiles));    % source files

% Safety: clear "paste into generated C" field
set_param(modelName,'CustomSourceCode','');
set_param(modelName,'CustomLibraryCode','');
set_param(modelName,'CustomHeaderCode','');   
set_param(modelName,'CustomInclude','');
set_param(modelName,'CustomSource','');
set_param(modelName,'CustomLibraries','');

end
