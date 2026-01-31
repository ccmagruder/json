# default.nix
{ lib, stdenv, cmake, cudaPackages, gtest}:

stdenv.mkDerivation {
  pname = "json-lib";
  version = "0.0.5";

  src = ./.;

  nativeBuildInputs = [
    cmake
  ];

  buildInputs = [
    gtest
  ];

  doCheck = true;

  checkPhase = ''
    runHook preCheck
    ctest --output-on-failure
    runHook postCheck
  '';


  meta = with lib; {
    description = "A JSON deserialization library.";
    platforms = platforms.linux;
  };
}
