# TODO

See `TODO.md` in each repos.

## Ubuntu Development Environment

- Do not deparate enlistment or control panel, new workflow should be:
  - Clone `Tools` repo in some place.
  - cd to a target folder, which you want to create the desktop launcher icon.
  - source `Tools/Ubuntu/start.sh`.
  - ask for `<NAME>.desktop` with `<TITLE>`, clone all repos in the folder containing `Tools`. If other repos exist, ask for choices:
    - Only create the desktop launcher icon.
    - Clone missing repos.
    - `rm -rf` all repos except `Tools`.
  - `<NAME>.desktop` will source `Tools/Ubuntu/start-enlistment.sh`.
    - `vapt`, `vssh` are moved here.
    - `venlist` is no longer needed because `start.sh` does the job.
- Update bash scripts to support VC++ Shared Items Project.
  - Consider recognize referenced projects automatically.

## GacUI Tutorials

## New Repos

- Hero DB
- VlppParser2
