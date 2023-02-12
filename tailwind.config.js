/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./src/**/*.{js,jsx,ts,tsx}"],
  theme: {
    extend: {
      gridTemplateColumns: {
        "auto-1": "repeat(1, auto)",
        "auto-2": "repeat(2, auto)",
        "auto-3": "repeat(3, auto)",
      },
    },
  },
  plugins: [],
};
