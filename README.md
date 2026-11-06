# Public Speaking Practice Evaluator - CAP455 CA1

Student: Saurabh kumar | Roll / Registration No.: 12611227 | Section: D1P2635

CA1: Design & Create, Units I-II. The application uses manually entered speaking-practice records. It supports in-memory Add, View All and Search by ID, with input validation and unique session IDs. Up to 50 sessions are stored.

## Build and run

From this folder in Windows PowerShell:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic src/main.cpp -o speaking.exe
.\speaking.exe
Get-Content data\sample_input.txt | .\speaking.exe
Get-Content tests\T15_input.txt | .\speaking.exe
```

On Linux or macOS, compile to `speaking` and use `./speaking < data/sample_input.txt`.

## Data and feedback

- Session ID: 1-9999, unique.
- Speaker name and speech topic: nonblank strings.
- Duration: 30-1800 seconds.
- Total spoken words (including fillers): 1-5000.
- Filler words: 0 through total spoken words.
- Words per minute = words * 60.0 / durationSec.
- Filler percentage = fillers * 100.0 / words.
- Project-defined pace labels: below 110 = Slow; 110-160 = Balanced; above 160 = Fast.
- Filler percentage at most 5 = Controlled; above 5 = Reduce fillers.

These thresholds are simple project demonstration rules, not institutional grading standards. There is no audio capture or automatic transcription. Records are cleared when the program exits.

## CA1 concepts and evidence

`PracticeSession` demonstrates private fields, a static count, an inline ID getter, a friend display function, `this`, strings, an array of objects, object pointers, and linear search. Input helpers reject invalid whole-line integers and blank text, and handle input termination.

`tests/verification.json` records 17 passed normal, invalid and boundary cases plus input-termination checks. Each case has an input and captured output file. `data` contains a three-session sample.

The 10-page PDF in `docs` contains the proposal, data dictionary, UML, flowchart, CA1 implementation explanation, tests, complete code, execution results and conclusion.

## AI assistance

AI assistance (OpenAI Codex) was used for implementation, testing and report preparation.
