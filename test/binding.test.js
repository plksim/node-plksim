const plksim = require("../lib/binding.js");

test('properties', () => {
  expect(plksim.nativeVersion).toMatch(/^[0-9]*\.[0-9]*\.[0-9]*$/);
});