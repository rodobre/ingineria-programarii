## Dependencies

Install apt packages with the versioning provided in `system_requirements.MD`

## Building

Build by executing build.sh on Linux (Debian/Ubuntu/CentOS RHEL), run `doxygen Doxyfile` to regenerate documentation

## Better visuals, better documentation

For better visuals, install `hugo` and run `./doxybook2 --input xml/ --output doxybook_output/documentation/content --config .doxybook/config.json --templates .doxybook/templates/`.
The, navigate to documentation using `cd doxybook_output/documentation` and run `hugo serve`.
