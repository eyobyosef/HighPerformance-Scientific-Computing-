% Define the limits of the cuboid
a = 0; b = 2; % x-limits
c = 0; d = 2; % y-limits
e = 0; f = 2; % z-limits

% Define the function
func = @(x,y,z) x.*y.*z;

% Use SPMD to split the work among 2 workers
spmd
    if labindex == 1
        % First worker handles the first half of the x-domain
        x_limit = [a, (a+b)/2];
    else
        % Second worker handles the second half of the x-domain
        x_limit = [(a+b)/2, b];
    end
 
    % Compute the integral for the given subdomain
    result = integral3(func, x_limit(1), x_limit(2), c, d, e, f);
end

% Combine results from both workers
total_integral = result{1} + result{2};

% Display the result
disp('Total integral value:');
disp(total_integral);
