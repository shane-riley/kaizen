# CS 1501 Project 0

## Specifications:
1. Create a new file `./app/src/main/java/cs1501_p0/Extra.java` that prints a brief message via `System.out.println()`.
	This message should include the string `"CS1501"` and be more than 20 characters, but less than 140 characters.
	Add this file to the git repository.
1. Change the String printed by `./app/src/main/java/cs1501_p0/Done.java` from `"NOT DONE"` to `"DONE"`.
1. Commit all changes to your repository.
1. Push your repository back to GitHub.
1. Submit your project via GradeScope.

## Submission Guidelines:
* **DO NOT** add `./app/build/` to your repository.
* Be sure to remember to push the latest copy of your code back to your GitHub
	repository before submitting. To submit, log into GradeScope from Canvas and
	have GradeScope pull your repository from GitHub.

## Additional Notes/Hints:
* The default file to run is `Done.java`, you can execute this by running `./gradlew run` on Linux or macOS.
* There is no easy way to run `Extra.java`, but there are tests setup to check that it is working. Running `./gradlew test` on Linux or macOS will run the tests to check both `Done.java` and `Extra.java`.
* Using Windows is not officially supported. You can log into `linux.cs.pitt.edu` via SSH (e.g., via PuTTY, using your Pitt username and password) to develop your projects or use the Windows Subsytem for Linux (WSL, https://docs.microsoft.com/en-us/windows/wsl/install-win10). If you choose to do native Windows development, Gradle should do a decent job of supporting this, but the instructor/TAs will be unable to support any technical difficulties you encouter.
* Don't forget to make `Extra.java` a part of the package `cs1501_p0`!
