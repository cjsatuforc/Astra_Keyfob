function [repeatingBits, repeatingNumber, initBits] = extractInfo(times,values)

    % Find Delta in time steps
    diffTimes = diff(times);

    % Find when there has been more than 1ms of no samples
    % This in indictivative of a message being sent
    timesLow = (diffTimes > 0.001);

    % Find the time sample numbers where this occurs so we can get the correct bits
    positionsLow = find(timesLow)';

    % Find the bits associated with the key code
    initBits = values(positionsLow(1)+1:positionsLow(2))';
    initBits = initBits(end-96:end);

    % Find bits of the incrementing code
    repeatingBits = values(positionsLow(3)+1:positionsLow(4))';

    % Find the dec value of the incrmenting bits
    repeatingNumber = binToDec(repeatingBits);

end 