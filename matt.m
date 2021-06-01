close all; clear all;

s = serial('COM8','BaudRate',9600);

fopen(s);

nBits = 16;

[y, Fs] = audioread('pupwhimper.mp3');
%player = audioplayer(y, Fs);

%figure(1);

 i =1;
 
%{ 
while(1)
    data(i) = str2double(fscanf(s));
    plot(data);
    ylim([0 10]);
    pause(0.01);
    i=i+1;
    
end
%}



while(1)
    newStr = split(fscanf(s), ",");
    disp(newStr);
    data(i) = str2double(newStr(2));
    disp(data(i));
    
    %data(i) = str2double(fscanf(s));
    %disp(data(i));
    
    
    if(data(i) > 0)
        %play(player);
        sound(y, Fs, nBits);
        pause(2);
        %stop(player);       
    end
    
    
    data(i) = str2double(newStr(1)); 
    disp(data(i));
    
    plot(data);
    ylim([0 10]);
    pause(0.01);
    
    
    %clear sound;
    %pause(0.01);
    i=i+1;
    
end
 


