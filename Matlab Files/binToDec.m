function output = binToDec(inputArray)
output = 0;
    for i = 0:(numel(inputArray)-1)
        if (inputArray(end))
            output = output + 2 .^ (i);
        end 
        inputArray(end) = [];
    end 
end 