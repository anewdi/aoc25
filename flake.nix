{
  description = "cpp flake";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.oldpkgs.url = "github:NixOS/nixpkgs/25.05";

  outputs =
    inputs:
    let
      system = "x86_64-linux";
      pkgs = import inputs.nixpkgs { inherit system; };
      oldpkgs = import inputs.oldpkgs { inherit system; };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gdb
          valgrind
          #need to do this untill #462747 is merged
          oldpkgs.clang-tools
        ];
      };
    };

}
