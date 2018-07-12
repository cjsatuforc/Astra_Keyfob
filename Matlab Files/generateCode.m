generatedKeyDelta = 0; % Change to alter how many steps ahead the new incrementing code is

% Get file name from user
fileNameOne = input('Please input the name of the file to be opened, including file extension: ', 's');

% Import file Into Matlab, format [time;value]
fileID = fopen(fileNameOne, 'r');

row1 = fscanf(fileID,'%s\n',2);
data = fscanf(fileID,"%f,'%d'\n",[2,Inf])';

fclose(fileID);

% Compute the bits!
[repeatingBits, repeatingNumber, initBits] = extractInfo(data(:,1),data(:,2));
% Display the values
initStr = num2str(sprintf('%i',initBits));

% Check we have the correct number of bits, otherwise throw an error 
if ((numel(setupStr)==97)&&(numel(repeatingBits)==34))
    fprintf('\nUnique Key Code:         %s \nUnique Key Code C Array: %s \n\n',initStr,cMatrixGeneration(initStr));
    fprintf("Incrementing Code:     %d \nNew Incrementing Code: %d\nNew Incrementing Code C Array: %s\n\n",repeatingNumber,repeatingNumber+generatedKeyDelta,cMatrixGeneration(dec2bin(repeatingNumber+generatedKeyDelta)));
else
    disp("Please check input data, decoded data incorrect.");
end
