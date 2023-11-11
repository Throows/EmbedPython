add_rules("mode.debug", "mode.release")
add_requires("python 3.11", "spdlog")

set_rundir("./bin/$(os)_$(arch)_$(mode)")
set_targetdir("./bin/$(os)_$(arch)_$(mode)")
set_warnings("allextra")
set_languages("c11", "cxx20")

set_project("EmbedPython")

-- Change according to your workspace (TODO: work on a fix for this)
pythonLib = "-L/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/lib"
pythonInclude = "/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Headers"

target("mygame")
    add_rules("python.library")
    add_ldflags(pythonLib)
    add_includedirs(pythonInclude)
    add_files("modules/mygame.cpp")
    add_packages("python")
target_end()

target("EPy")
	set_kind("binary")
	set_version("0.1.0")
	add_files("src/*.cpp")

	add_packages("python", "spdlog")
    add_ldflags(pythonLib)
    add_includedirs(pythonInclude, "modules")
    add_ldflags("-lpython3.11", {force = true})
    add_deps("mygame")
target_end()

after_build(function (target) 
    os.cp("$(projectdir)/scripts/*", "$(projectdir)/bin/$(os)_$(arch)_$(mode)/scripts/")
    os.mv("$(projectdir)/bin/$(os)_$(arch)_$(mode)/*.so", "$(projectdir)/bin/$(os)_$(arch)_$(mode)/scripts/")
end)