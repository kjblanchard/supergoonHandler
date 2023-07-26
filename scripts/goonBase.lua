INIT_TIME = 0


function InitializeBot()
    INIT_TIME = os.time()
    print('Hello world!, current time is ' .. INIT_TIME)
end

function UpdateBot()
    local elapsedTime = os.time() - INIT_TIME
    print('Elapsed time in MS is ' .. elapsedTime)
end
