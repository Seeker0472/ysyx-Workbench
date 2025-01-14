{
  description = "ysyx_workbench";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config = { allowUnfree = true; };
        };
        my-verilator = (pkgs.verilator.overrideAttrs (oldAttrs: rec {
          version = "5.008";
          src = pkgs.fetchFromGitHub {
            owner = "verilator";
            repo = "verilator";
            rev = "v${version}";
            sha256 = "0wqnn2r8kjbrm28c5qajldw5axmrkslds1957wz9r4qfyhd43qpr";
          };
          patches = [ ]; # 禁用所有补丁
        }));
        libyaml_cpp_0_7 = (pkgs.yaml-cpp.overrideAttrs (oldAttrs: rec {
          version = "0.7.0";
          src = pkgs.fetchFromGitHub {
            owner = "jbeder";
            repo = "yaml-cpp";
            rev = version;
            sha256 = "1nb8mwkj8ksr6abw1iv3i03fnlfqc1ixbm2gjlv4g7wzr1qmdlfs";
          };
          patches = [
            # https://github.com/jbeder/yaml-cpp/issues/774
            # https://github.com/jbeder/yaml-cpp/pull/1037
            (pkgs.fetchpatch {
              name = "yaml-cpp-Fix-generated-cmake-config.patch";
              url = "https://github.com/jbeder/yaml-cpp/commit/4f48727b365962e31451cd91027bd797bc7d2ee7.patch";
              hash = "sha256-jarZAh7NgwL3xXzxijDiAQmC/EC2WYfNMkYHEIQBPhM=";
            })
            # TODO: Remove with the next release, when https://github.com/jbeder/yaml-cpp/pull/1058 is available
            (pkgs.fetchpatch {
              name = "yaml-cpp-Fix-pc-paths-for-absolute-GNUInstallDirs.patch";
              url = "https://github.com/jbeder/yaml-cpp/commit/328d2d85e833be7cb5a0ab246cc3f5d7e16fc67a.patch";
              hash = "sha256-1M2rxfbVOrRH9kiImcwcEolXOP8DeDW9Cbu03+mB5Yk=";
            })
          ];

        }));

      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            pkgs.espresso
            # 指定verilator版本为5.008
            my-verilator
            # verilator
            pkgs.ffmpeg

            #build-essential
            pkgs.man
            #gcc-doc
            pkgs.git
            pkgs.gdb
            pkgs.readline #libreadline-dev
            pkgs.vim
            pkgs.gcc
            pkgs.python3
            pkgs.SDL2
            pkgs.SDL2_image
            pkgs.SDL2_ttf
            # verilator start
            pkgs.perl
            pkgs.flex
            pkgs.bison
            pkgs.ccache
            pkgs.gperftools
            pkgs.numactl
            # verilator end
            pkgs.llvm_18
            pkgs.mill
            pkgs.pkgsCross.riscv64.buildPackages.gcc
            pkgs.pkgsCross.riscv64.buildPackages.binutils
            pkgs.bear    
	# TODO:add more!!!
            pkgs.ncurses
            pkgs.clang-tools
            pkgs.zulu17
            pkgs.yosys
            # libyaml_cpp_0_7
            pkgs.pkg-config
            python312 
            python312Packages.matplotlib
            python312Packages.numpy
            pkgs.stdenv.cc.cc
            pkgs.dtc
            pkgs.boost
          ];
          hardeningDisable = [ "fortify" ];
          # hardeningDisable = [ "all" ];
          
          # LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.glibc}/bin";

          NIX_LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            # 添加需要的库
            pkgs.ncurses
            pkgs.readline
            pkgs.SDL2
            pkgs.SDL2_image
            pkgs.SDL2_ttf
            pkgs.libz
            pkgs.llvmPackages_latest.llvm
            # yosys-sta libs
            # pkgs.yaml-cpp
            # 以下是yosys-sta的依赖
            libyaml_cpp_0_7
            pkgs.libgcc.lib
            pkgs.gmp
            pkgs.tcl
            pkgs.libunwind
            pkgs.stdenv.cc.cc
            pkgs.boost
          ];
          NIX_LD = pkgs.lib.fileContents "${pkgs.stdenv.cc}/nix-support/dynamic-linker";
        };
      }
    );
}

