
import { IconName } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import "./App.css";

function generateFeatureBox(icon: IconName, title: string, message: string) {
  return (
    <div className="feature-box" key={title}>
      <span className="title"><FontAwesomeIcon icon={['fas', icon]} className="icon" /> {title}</span>
      <span className="message">{message}</span>
    </div>
  );
}

function App() {
  return (
    <div className="App text-gray-100">
      <div className="background-container"></div>
      <div className="grid-container flex flex-col align-middle items-center justify-center text-center">
        <span className="mt-[-15vh] p-5 same-bg-shadow">
          <h1 className="md:text-5xl sm:text-3xl font-bold text-2xl">
            Call of Duty:&nbsp;
            <span className="text-transparent bg-clip-text bg-gradient-to-r from-orange-500 to-red-600">
              Black Ops III
            </span>
            <br />
          </h1>
          <h2 className="md:text-4xl sm:text-2xl text-xl font-bold pt-2 md:pt-4 text-[#eeebe79d]">
            The way it was meant to be.
          </h2>
          <span className="button-container text-center flex gap-8 mt-8 md:mt-12 align-middle items-center justify-center">
            <button disabled={true} title="soon™️">
              Download
            </button>
            <a
              rel="noreferrer"
              target="_blank"
              href="https://github.com/momo5502/boiii"
            >
              GitHub
            </a>
            <a
              rel="noreferrer"
              target="_blank"
              href="https://linktr.ee/momo5502"
            >
              Donate
            </a>
          </span>
        </span>

        <div className="mouse-scroll"><span></span></div>
      </div>
      <div className="feature-container">
        <span className="w-100 font-bold md:text-4xl sm:text-2xl text-xl text-center block text-[#f4f0ebc6]">What does <span className="text-transparent bg-clip-text bg-gradient-to-r from-orange-500 to-red-600">
              BOIII
            </span> offer?</span>
        <hr className="mt-8 mb-16 border-[#f4f0eb52]"></hr>
        <div className="feature-grid">
          {[
            generateFeatureBox("lock", "Improved Security", "Security vulnerabilities have been patched providing a safer gaming experience."),
            generateFeatureBox("code", "Improved Stability", "Issues and bugs have been fixed resulting in fewer crashes and instabilities."),
            generateFeatureBox("gauge-high", "Improved Performance", "Performance issues have been addressed leading to higher FPS and smoother gameplay."),
            generateFeatureBox("ranking-star", "Ranked Servers", "Unlike in the original game, ranking up on dedicated servers is possible."),
            generateFeatureBox("cloud", "Workshop Support", "Custom maps and content from the Steam workshop is completely supported."),
            generateFeatureBox("gamepad", "Controller Support", "Want to play using mouse and keyboard or your favourite gamepad? You decide."),
          ]}
        </div>
      </div>
    </div>
  );
}

export default App;
