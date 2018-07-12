% Get file names from user
fileNameOne = input('Please input the name of the first file to be opened, including file extension: ', 's');
fileNameTwo = input('Please input the name of the second file to be opened, including file extension: ', 's');

% Import first file Into Matlab, format [time;value]
fileID = fopen(fileNameOne, 'r');

row1 = fscanf(fileID,'%s\n',2); % Dont need this data
dataOne = fscanf(fileID,"%f,'%d'\n",[2,Inf])';

fclose(fileID);

% Import second file Into Matlab, format [time;value]
fileID = fopen(fileNameTwo, 'r');

row1 = fscanf(fileID,'%s\n',2);
dataTwo = fscanf(fileID,"%f,'%d'\n",[2,Inf])';

fclose(fileID);

% Compute the bits!
[oneRepeatingBits, oneRepeatingNumber, oneSetupBits] = extractInfo(dataOne(:,1),dataOne(:,2));
[twoRepeatingBits, twoRepeatingNumber, twoSetupBits] = extractInfo(dataTwo(:,1),dataTwo(:,2));

% Display the values
diffInitBits = [];
for i = 1:numel(oneSetupBits)
    if (oneSetupBits(i) == twoSetupBits(i))
        diffInitBits(end+1) = 0;
    else
        diffInitBits(end+1) = 1;
    end 
end 

diffInitStr = sprintf('%i',diffInitBits);
oneSetupStr = sprintf('%i',oneSetupBits);
twoSetupStr = sprintf('%i',twoSetupBits);

fprintf('\nFirst Key Code:       %s \nSecond Key Code:      %s \nDiff of Key Codes:    %s \n\nFirst Rolling Code:   %d\nSecond Rolling Code:  %d \n\n',oneSetupStr, twoSetupStr, diffInitStr, oneRepeatingNumber, twoRepeatingNumber)