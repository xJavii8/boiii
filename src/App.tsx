import "./App.css";

function App() {
  return (
    <div className="App bg-[#151515] text-gray-100">
      <div className="grid-container flex flex-col align-middle items-center justify-center text-center">
        <span className="mt-[-15vh] bg-[#151515] p-5 same-bg-shadow">
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
      </div>
    </div>
  );
}

export default App;
