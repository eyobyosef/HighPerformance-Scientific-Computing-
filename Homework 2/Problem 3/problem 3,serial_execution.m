function t1 = serial_execution(n)
    tic
    for i=1:n
        timeconsumingfun
    end
    t1 = toc;
end
