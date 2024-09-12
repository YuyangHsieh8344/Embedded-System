serialPort = 'COM5';  
baudRate = 9600;

clear s;
% Create serial object
s = serialport(serialPort, baudRate);



% Set limits for the axis to ensure that the 
% acceleration values do not overflow
xLimit = [0, 1024]; 
yLimit = [0, 1024];
zLimit = [0, 1024];

% Loop for 1000 iterations
for i = 1:1000
    % read the line from the device 
    data = readline(s);
    
    %  split it into an array
    dataArray = split(data, " "); 

    % Check if the array has three elements for x, y, and z
    if length(dataArray) == 3
        % Convert string to a double value.
        xData = double(dataArray(1));
        yData = double(dataArray(2));
        zData = double(dataArray(3));
        
        % Plot x, y and z axis with a marker ‘o’
        plot3(xData, yData, zData, 'o');
        
        % Set axis limits to avoid overflow
        xlim(xLimit);
        ylim(yLimit);
        zlim(zLimit);
        
        % Label the axes
        xlabel('X-Axis'); 
        ylabel('Y-Axis'); 
        zlabel('Z-Axis');
        
        % Create a grid
        grid on;
        
        % Display the latest data point
        title(sprintf('Latest Data Point: X=%.2f, Y=%.2f, Z=%.2f', dataArray(1), dataArray(2), dataArray(3)));
        
        % Update the plot
        drawnow;
    end
end

% Close the serial connection after 1000 readings
delete(s);
clear s;
