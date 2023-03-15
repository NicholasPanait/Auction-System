From a Linux Terminal:

- Navigate into the frontend test folder (CSCI3060FINALPROJECT/tests/frontend)

- In this directory there are 4 important directories

    - input -> the input for each test case
    
    - expected_output -> the expected output for each test case

    - outputs -> the terminal and file outputs for each test

    - comparison -> the result of the 'diff' command used to compare the related files in ouputs and expected_output

- From the same directory (CSCI3060FINALPROJECT/tests/frontend)
  Run the command 'bash run_tests.sh' (No quotes)

  This will run each test case and populate the outputs folder, as well as the comparison folder.