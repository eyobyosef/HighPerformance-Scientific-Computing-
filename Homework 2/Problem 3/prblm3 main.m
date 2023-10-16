% Scenario runs
n_values = [4, 8, 16]; % Small, Medium, Large
for i=1:length(n_values)
    n = n_values(i);
    
    T1 = serial_execution(n);
    Tp = parallel_execution(n);
    
    % Calculate speedup and efficiency
    speedup = T1 / Tp;
    efficiency = speedup / n; % n is also the number of cores in our case
    
    fprintf('For n = %d:\n', n);
    fprintf('Speedup: %.2f\n', speedup);
    fprintf('Average Efficiency: %.2f\n\n', efficiency);
end
