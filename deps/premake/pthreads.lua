pthreads = {
	source = path.join(dependencies.basePath, "pthreads"),
}

function pthreads.import()
	links {
		"pthreads"
	}

	pthreads.includes()
end

function pthreads.includes()
	includedirs {
		pthreads.source,
	}

	
	defines {
		"HAVE_CONFIG_H",
	}
end

function pthreads.project()
	project "pthreads"
		language "C"

		pthreads.includes()

		files {
			path.join(pthreads.source, "pthread.c"),
		}

		warnings "Off"
		kind "StaticLib"
end

table.insert(dependencies, pthreads)
