# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ogro_invasion.Debug:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/Debug/ogro_invasion:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/Debug/ogro_invasion


PostBuild.ogro_invasion.Release:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/Release/ogro_invasion:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/Release/ogro_invasion


PostBuild.ogro_invasion.MinSizeRel:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/MinSizeRel/ogro_invasion:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/MinSizeRel/ogro_invasion


PostBuild.ogro_invasion.RelWithDebInfo:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/RelWithDebInfo/ogro_invasion:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_13/ogro_invasion/RelWithDebInfo/ogro_invasion




# For each target create a dummy ruleso the target does not have to exist
