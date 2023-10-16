function tp = parallel_execution(n)
    % Ensure parallel pool exists
    if isempty(gcp())
        parpool();
    end
    
    tic
    parfor i=1:n
        timeconsumingfun
    end
    tp = toc;
end
