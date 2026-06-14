clear; clc;

% --- 1. Settings ---
arduinoPort = "COM7";  % CHANGE TO YOUR PORT
baudRate = 9600;

% --- 2. Setup Arduino Connection ---
disp(['Connecting to Arduino on ', arduinoPort, '...']);
try
    arduino = serialport(arduinoPort, baudRate);
    configureTerminator(arduino, "CR/LF");
    disp('Arduino Connected!');
catch
    error('Failed to connect. Check Arduino connection and COM port.');
end

% --- 3. Load AI Model ---
disp('Loading AI Model...');
load('trained_gesture_net.mat');

inputSize = netTrained.Layers(1).InputSize(1:2);
cam = webcam();

disp('------------------------------------------------');
disp('ROBOT CONTROL LIVE');
disp('Sending commands: F, L, R, S');
disp('------------------------------------------------');

figure('Name', 'Robot Controller');

lastCommand = '';

while true

    img = snapshot(cam);
    imgResized = imresize(img, inputSize);

    [label, scores] = classify(netTrained, imgResized);

    confidence = max(scores);
    gesture = char(label);

    if confidence > 0.50

        cmdToSend = '';

        switch gesture
            case 'forward'
                cmdToSend = 'F';

            case 'left'
                cmdToSend = 'L';

            case 'right'
                cmdToSend = 'R';

            case 'stop'
                cmdToSend = 'S';
        end

        if ~strcmp(cmdToSend, lastCommand)
            write(arduino, cmdToSend, "char");
            lastCommand = cmdToSend;

            disp(['Sent to Robot: ', cmdToSend]);
        end

    else

        if ~strcmp(lastCommand, 'S')
            write(arduino, 'S', "char");
            lastCommand = 'S';

            disp('Unsure - Stopping Robot');
        end

    end

    imshow(img);
    title(['Robot Action: ', gesture], ...
        'FontSize', 18, ...
        'Color', 'm');

    drawnow;

end
