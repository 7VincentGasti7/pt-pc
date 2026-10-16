# P.T. PC Port 1.0.5

A hotfix for 1.0.4. Update from inside the game, or run the setup over your existing installation: your game archives,
settings, saves and mods stay.

## Crashes and starts

- **Linux and macOS:** 1.0.4 crashed at every start. Fixed. Crash reports on Linux and macOS now log the signal and the
  stack, and stderr goes to pt-stderr.log.
- **DirectX 12:** GPUs that cannot run everything the DirectX 12 renderer needs (some Intel GPUs) crashed at the first
  start. The game now checks every feature it uses before offering DirectX 12, and a failed DirectX 12 start goes back to
  Vulkan for the next start.
- The first start still asks which rendering API to use, with DirectX 12 first. Pressing Enter now picks Vulkan, so a
  quick Enter on a GPU that cannot run DirectX 12 no longer leaves the game crashing. A choice you already made stays.
- **Game+:** the bathtub Lisa could vanish or crash the game after the ending's restart. Fixed.
- The update check, the DLSS runtime discovery and the FSR probe can no longer stop the game from starting.

## DirectX 12

- A frame limit no longer switches Reflex Low Latency on by itself, so a 60 fps limit holds.
- **FSR 4 and FSR 3.1** on DirectX 12 now use AMD's FSR SDK loader and upscaler DLLs. The settings say why FSR 4 is not
  offered when your GPU cannot run it.
- pt.log records per frame work and memory use every 10 seconds, to help with performance reports.

## Path tracing and ray tracing

- **The flashlight's light bounced by the bathroom mirror** is back on the wall in Ultra and Path traced. Only its outline
  showed, and the mirror showed no reflected room in Path traced.
- Path traced: the player's arm in the bathroom mirror no longer shows jagged dark shapes.
- Path traced: the radio table lamp in the hallway no longer lights a stepped block of wall through the window casing and
  the door frame.
- Path traced window glass blurs its reflection evenly over the bars and the frame's edges.
- The bathroom mirror and the glass now show their reflection at any distance in Path traced (the wall showed through).
- The window and picture glass reflect the player's body in Path traced, and the globe lamps glow in reflections.
- Path traced glass reflections stay put on the glass instead of sliding as you move.
- Path traced glass keeps its own dust and grime, as in Ultra.
- DLSS Ray Reconstruction works on every ray quality with a traced effect, not only Path traced.

## DLSS 5 route

- A ReShade loaded before the game is recognised as the route's, and the crash marker is set before ReShade loads, so a
  crash at start turns the route off for the next start.
- On starts that do not run the route, its add-on is switched off, so a ReShade installed for every program on the system
  no longer crashes Vulkan starts.
- Switching DLSS 5 on in play crashed on RTX 50 GPUs. The game no longer creates a short-lived test device before its
  own when the route is loaded, which is the likely cause. If DLSS 5 still crashes, the next start turns it off; please
  send the crash report.

## Controls and menus

- **Gyro:** the drift is calibrated continuously while the controller rests, and Accessibility has a Calibrate gyro row (gyro_tightening in pt.ini smooths slow turns).
- PC settings lists scroll with the mouse wheel and show scroll arrows and a scrollbar.
- A held music key or a stick near the threshold no longer repeats the menu sound.
- Lisa's footsteps no longer play through the pause menu.
- The window comes to the front at start.
- F9 logs the camera pose in pt.log again, so you can tell us exactly where you saw a problem.

## Updates

- The update information is signed and travels inside the setup, so in-game updates only download the files that changed.
