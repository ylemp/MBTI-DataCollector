# Data collector

## Task
Implement a service that collects system information upon reception of a trigger event.
The trigger event is raised when existence of a file with a certain name in a specified directory is detected.

The following features must be implemented:
* Trigger detection
  * Detect creation of a file in a somehow specified directory
  * Make the directory configurable via commandline parameter
  * Only trigger on files with names following this format:
    * Starts with `core.<variable name of a service>.`
    * Ends with `lz4`
    * Contains one or more hexadecimal id separated by dots
    * Example: `core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4`
* Collected data shall be:
  * Individual files, as well as whole directories and their contents, recursively, configured via command line parameter
* Store the collected data in a configurable directory, create a `tar`-archive of the aforementioned contents
  * Give the resulting file a unique name.
* Add tests to make sure your application is working,
  * How tests are implemented is up to you

## Things to keep in mind
* Implement your collection in a way such that it can be extended to collect other data of various forms later.
* Use modern C++!
* Use the platform of your choice (Linux, BSD, MacOS, Windows, etc.)
  * We use Linux but everything else is cool, too.

