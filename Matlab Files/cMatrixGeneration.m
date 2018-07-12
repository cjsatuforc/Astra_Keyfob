function outputString = cMatrixGeneration(charArray)

    for i = 1 : length(charArray)
        vector{i} = num2str(charArray(i)) - '0';
    end
    vector = cell2mat(vector);
    
    init = '{';
    second = num2str(vector(1));
    finish = '};';

    middle = sprintf(",%d",vector(2:end));
    
    outputString = strcat(init,second,middle,finish);
end 