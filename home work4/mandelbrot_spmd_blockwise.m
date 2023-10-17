function mandelbrot_spmd_blockwise(blockSize)

    % Define the domain
    domainSize = 2000;  % Example for a 2000x2000 domain
    blocksPerDimension = domainSize / blockSize;
    
    % Create a Composite to store each worker's data
    mandelblock = Composite();
    
    spmd
        % Determine block bounds
        [xStart, xEnd, yStart, yEnd] = determineBounds(labindex, blockSize, blocksPerDimension);
        
        % Compute the Mandelbrot set for the block
        mandelblockPart = computeMandelbrotBlock(xStart, xEnd, yStart, yEnd);
        
        % Store the result in the Composite variable
        mandelblock{labindex} = mandelblockPart;
        
        % Print worker output
        fprintf('Worker %d: \n  Worker: %d, xStart: %d, xEnd: %d, yStart: %d, yEnd: %d\n', ...
            labindex, labindex, xStart, xEnd, yStart, yEnd);
    end
    
    % Convert the Composite to a regular cell array
    mandelblock = mandelblock(:);
    
    % Reshape the array and concatenate to form the full image
    fullMandel = cell2mat(reshape(mandelblock, [blocksPerDimension, blocksPerDimension])');
    
    % Display the result
    imagesc(fullMandel);
    colormap([0 0 0; jet(255)]);
    axis equal off;

end

function [xStart, xEnd, yStart, yEnd] = determineBounds(workerIndex, blockSize, blocksPerDimension)
    row = ceil(workerIndex / blocksPerDimension);
    col = mod(workerIndex-1, blocksPerDimension) + 1;

    xStart = (col-1) * blockSize + 1;
    xEnd = col * blockSize;
    yStart = (row-1) * blockSize + 1;
    yEnd = row * blockSize;
end

function mandelblock = computeMandelbrotBlock(xStart, xEnd, yStart, yEnd)
    % ... (This function remains unchanged and computes the Mandelbrot set for the given block bounds)
end
