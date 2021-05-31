close all; clear all;

s = serial('COM9','BaudRate',9600);

fopen(s);

figure(1);

 i =1;
while(1)
    data(i) = str2double(fscanf(s));
    plot(data);
    ylim([0 10]);
    pause(0.05);
    i=i+1;
    
end


