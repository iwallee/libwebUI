#ifndef PlatformImpl_h
#define PlatformImpl_h

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "base/timer/timer.h"
#include "base/platform_file.h"
#include "../../platform/Platform.h"
#include "../../platform/WebNonCopyable.h"

#include "../../platform/win/WebThemeEngine.h"
#include "WebThemeEngineImpl.h"


using namespace blink;

namespace base{
    class MessageLoop;
}

class PlatformImpl : public blink::Platform
{
public:
    PlatformImpl();

    ~PlatformImpl();
    // May return null.
    virtual WebCookieJar* cookieJar();

    // Must return non-null.
    virtual WebClipboard* clipboard();

    // Must return non-null.
    virtual WebFileUtilities* fileUtilities();

    // Must return non-null.
    virtual WebMimeRegistry* mimeRegistry();

    // May return null if sandbox support is not necessary
    virtual WebSandboxSupport* sandboxSupport();

    // May return null on some platforms.
    virtual WebThemeEngine* themeEngine();

    virtual WebFallbackThemeEngine* fallbackThemeEngine();

    // May return null.
    virtual WebSpeechSynthesizer* createSpeechSynthesizer(WebSpeechSynthesizerClient*);


    // Media --------------------------------------------------------------

    // May return null.
    virtual WebContentDecryptionModule* createContentDecryptionModule(const WebString& keySystem);


    // Audio --------------------------------------------------------------

    virtual double audioHardwareSampleRate();
    virtual size_t audioHardwareBufferSize();
    virtual unsigned audioHardwareOutputChannels();

    // Creates a device for audio I/O.
    // Pass in (numberOfInputChannels > 0) if live/local audio input is desired.
    virtual WebAudioDevice* createAudioDevice(size_t bufferSize, unsigned numberOfInputChannels, unsigned numberOfChannels, double sampleRate, WebAudioDevice::RenderCallback*, const WebString& deviceId);

    // FIXME: remove deprecated APIs once chromium switches over to new method.
    virtual WebAudioDevice* createAudioDevice(size_t bufferSize, unsigned numberOfChannels, double sampleRate, WebAudioDevice::RenderCallback*);
    virtual WebAudioDevice* createAudioDevice(size_t bufferSize, unsigned numberOfInputChannels, unsigned numberOfChannels, double sampleRate, WebAudioDevice::RenderCallback*);


    // MIDI ----------------------------------------------------------------

    // Creates a platform dependent WebMIDIAccessor. MIDIAccessor under platform
    // creates and owns it.
    virtual WebMIDIAccessor* createMIDIAccessor(WebMIDIAccessorClient*);


    // Blob ----------------------------------------------------------------

    // Must return non-null.
    virtual WebBlobRegistry* blobRegistry();


    // Database ------------------------------------------------------------

    // Opens a database file; dirHandle should be 0 if the caller does not need
    // a handle to the directory containing this file
    virtual Platform::FileHandle databaseOpenFile(const WebString& vfsFileName, int desiredFlags);

    // Deletes a database file and returns the error code
    virtual int databaseDeleteFile(const WebString& vfsFileName, bool syncDir);

    // Returns the attributes of the given database file
    virtual long databaseGetFileAttributes(const WebString& vfsFileName);

    // Returns the size of the given database file
    virtual long long databaseGetFileSize(const WebString& vfsFileName);

    // Returns the space available for the given origin
    virtual long long databaseGetSpaceAvailableForOrigin(const blink::WebString& originIdentifier);


    // DOM Storage --------------------------------------------------

    // Return a LocalStorage namespace
    virtual WebStorageNamespace* createLocalStorageNamespace();


    // FileSystem ----------------------------------------------------------

    // Must return non-null.
    virtual WebFileSystem* fileSystem();


    // IDN conversion ------------------------------------------------------

    virtual WebString convertIDNToUnicode(const WebString& host, const WebString& languages);


    // IndexedDB ----------------------------------------------------------

    // Must return non-null.
    virtual WebIDBFactory* idbFactory();


    // Gamepad -------------------------------------------------------------

    virtual void sampleGamepads(WebGamepads& into);


    // History -------------------------------------------------------------

    // Returns the hash for the given canonicalized URL for use in visited
    // link coloring.
    virtual unsigned long long visitedLinkHash(
        const char* canonicalURL, size_t length);

    // Returns whether the given link hash is in the user's history. The
    // hash must have been generated by calling VisitedLinkHash().
    virtual bool isLinkVisited(unsigned long long linkHash);


    // Keygen --------------------------------------------------------------

    // Handle the <keygen> tag for generating client certificates
    // Returns a base64 encoded signed copy of a public key from a newly
    // generated key pair and the supplied challenge string. keySizeindex
    // specifies the strength of the key.
    virtual WebString signedPublicKeyAndChallengeString(unsigned keySizeIndex,
        const WebString& challenge,
        const WebURL& url);


    // Memory --------------------------------------------------------------

    // Returns the current space allocated for the pagefile, in MB.
    // That is committed size for Windows and virtual memory size for POSIX
    virtual size_t memoryUsageMB();

    // Same as above, but always returns actual value, without any caches.
    virtual size_t actualMemoryUsageMB() ;

    // Return the physical memory of the current machine, in MB.
    virtual size_t physicalMemoryMB() ;

    // Return the number of of processors of the current machine.
    virtual size_t numberOfProcessors() ;

    // Returns private and shared usage, in bytes. Private bytes is the amount of
    // memory currently allocated to this process that cannot be shared. Returns
    // false on platform specific error conditions.
    virtual bool processMemorySizesInBytes(size_t* privateBytes, size_t* sharedBytes);

    // Requests private and shared usage, in bytes. Private bytes is the amount of
    // memory currently allocated to this process that cannot be shared.
    // The callback ownership is passed to the callee.
    virtual void requestProcessMemorySizes(ProcessMemorySizesCallback* requestCallback);

    // Reports number of bytes used by memory allocator for internal needs.
    // Returns true if the size has been reported, or false otherwise.
    virtual bool memoryAllocatorWasteInBytes(size_t*);

    // Allocates discardable memory. May return 0, even if the platform supports
    // discardable memory. If nonzero, however, then the WebDiscardableMmeory is
    // returned in an locked state. You may use its underlying data() member
    // directly, taking care to unlock it when you are ready to let it become
    // discardable.
    virtual WebDiscardableMemory* allocateAndLockDiscardableMemory(size_t bytes) ;

    // A wrapper for tcmalloc's HeapProfilerStart();
    virtual void startHeapProfiling(const WebString& /*prefix*/);
    // A wrapper for tcmalloc's HeapProfilerStop();
    virtual void stopHeapProfiling() ;
    // A wrapper for tcmalloc's HeapProfilerDump()
    virtual void dumpHeapProfiling(const WebString& /*reason*/);
    // A wrapper for tcmalloc's GetHeapProfile()
    virtual WebString getHeapProfile();

    // Returns the maximum amount of memory a decoded image should be allowed.
    // See comments on ImageDecoder::m_maxDecodedBytes.
    virtual size_t maxDecodedImageBytes();


    // Message Ports -------------------------------------------------------

    // Creates a Message Port Channel. This can be called on any thread.
    // The returned object should only be used on the thread it was created on.
    virtual WebMessagePortChannel* createMessagePortChannel() ;


    // Network -------------------------------------------------------------

    // Returns a new WebURLLoader instance.
    virtual WebURLLoader* createURLLoader();

    // May return null.
    virtual WebPrescientNetworking* prescientNetworking() ;

    // Returns a new WebSocketStreamHandle instance.
    virtual WebSocketStreamHandle* createSocketStreamHandle() ;

    // Returns a new WebSocketHandle instance.
    virtual WebSocketHandle* createWebSocketHandle() ;

    // Returns the User-Agent string that should be used for the given URL.
    virtual WebString userAgent(const WebURL&);

    // A suggestion to cache this metadata in association with this URL.
    virtual void cacheMetadata(const WebURL&, double responseTime, const char* data, size_t dataSize);

    // Returns the decoded data url if url had a supported mimetype and parsing was successful.
    virtual WebData parseDataURL(const WebURL& url, WebString& mimetype, WebString& charset);

    virtual WebURLError cancelledError(const WebURL&) const;


    // Plugins -------------------------------------------------------------

    // If refresh is true, then cached information should not be used to
    // satisfy this call.
    virtual void getPluginList(bool refresh, WebPluginListBuilder*);


    // Public Suffix List --------------------------------------------------

    // May return null on some platforms.
    virtual WebPublicSuffixList* publicSuffixList() ;


    // Resources -----------------------------------------------------------

    // Returns a localized string resource (with substitution parameters).
    virtual WebString queryLocalizedString(WebLocalizedString::Name);
    virtual WebString queryLocalizedString(WebLocalizedString::Name, const WebString& parameter);
    virtual WebString queryLocalizedString(WebLocalizedString::Name, const WebString& parameter1, const WebString& parameter2);


    // Threads -------------------------------------------------------

    // Creates an embedder-defined thread.
    virtual WebThread* createThread(const char* name) ;

    // Returns an interface to the current thread. This is owned by the
    // embedder.
    virtual WebThread* currentThread() ;


    // Profiling -----------------------------------------------------------

    virtual void decrementStatsCounter(const char* name);
    virtual void incrementStatsCounter(const char* name);


    // Resources -----------------------------------------------------------

    // Returns a blob of data corresponding to the named resource.
    virtual WebData loadResource(const char* name);

    // Decodes the in-memory audio file data and returns the linear PCM audio data in the destinationBus.
    // A sample-rate conversion to sampleRate will occur if the file data is at a different sample-rate.
    // Returns true on success.
    virtual bool loadAudioResource(WebAudioBus* destinationBus, const char* audioFileData, size_t dataSize, double sampleRate);


    // Screen -------------------------------------------------------------

    // Supplies the system monitor color profile.
    virtual void screenColorProfile(WebVector<char>* profile);


    // Sudden Termination --------------------------------------------------

    // Disable/Enable sudden termination.
    virtual void suddenTerminationChanged(bool enabled);


    // System --------------------------------------------------------------

    // Returns a value such as "en-US".
    virtual WebString defaultLocale();

    // Wall clock time in seconds since the epoch.
    virtual double currentTime() ;

    // Monotonically increasing time in seconds from an arbitrary fixed point in the past.
    // This function is expected to return at least millisecond-precision values. For this reason,
    // it is recommended that the fixed point be no further in the past than the epoch.
    virtual double monotonicallyIncreasingTime();

    // WebKit clients must implement this funcion if they use cryptographic randomness.
    virtual void cryptographicallyRandomValues(unsigned char* buffer, size_t length);

    // Delayed work is driven by a shared timer.
    virtual void setSharedTimerFiredFunction(SharedTimerFunction timerFunction);
    virtual void setSharedTimerFireInterval(double interval_seconds);
    virtual void stopSharedTimer();
    // Callable from a background WebKit thread.
    virtual void callOnMainThread(void(*func)(void*), void* context);

    // Vibration -----------------------------------------------------------

    // Starts a vibration for the given duration in milliseconds. If there is currently an active
    // vibration it will be cancelled before the new one is started.
    virtual void vibrate(unsigned time) ;

    // Cancels the current vibration, if there is one.
    virtual void cancelVibration() ;


    // Testing -------------------------------------------------------------
    // Get a pointer to testing support interfaces. Will not be available in production builds.
    virtual WebUnitTestSupport* unitTestSupport() ;


    // Tracing -------------------------------------------------------------

    // Get a pointer to the enabled state of the given trace category. The
    // embedder can dynamically change the enabled state as trace event
    // recording is started and stopped by the application. Only long-lived
    // literal strings should be given as the category name. The implementation
    // expects the returned pointer to be held permanently in a local static. If
    // the unsigned char is non-zero, tracing is enabled. If tracing is enabled,
    // addTraceEvent is expected to be called by the trace event macros.
    virtual const unsigned char* getTraceCategoryEnabledFlag(const char* categoryName);

    // Get a pointer to a global state of the given thread. An embedder is
    // expected to update the global state as the state of the embedder changes.
    // A sampling thread in the Chromium side reads the global state periodically
    // and reflects the sampling profiled results into about:tracing.
    virtual Platform::TraceEventAPIAtomicWord* getTraceSamplingState(const unsigned bucketName);


    // Add a trace event to the platform tracing system. Depending on the actual
    // enabled state, this event may be recorded or dropped.
    // - phase specifies the type of event:
    //   - BEGIN ('B'): Marks the beginning of a scoped event.
    //   - END ('E'): Marks the end of a scoped event.
    //   - COMPLETE ('X'): Marks the beginning of a scoped event, but doesn't
    //     need a matching END event. Instead, at the end of the scope,
    //     updateTraceEventDuration() must be called with the TraceEventHandle
    //     returned from addTraceEvent().
    //   - INSTANT ('I'): Standalone, instantaneous event.
    //   - START ('S'): Marks the beginning of an asynchronous event (the end
    //     event can occur in a different scope or thread). The id parameter is
    //     used to match START/FINISH pairs.
    //   - FINISH ('F'): Marks the end of an asynchronous event.
    //   - COUNTER ('C'): Used to trace integer quantities that change over
    //     time. The argument values are expected to be of type int.
    //   - METADATA ('M'): Reserved for internal use.
    // - categoryEnabled is the pointer returned by getTraceCategoryEnabledFlag.
    // - name is the name of the event. Also used to match BEGIN/END and
    //   START/FINISH pairs.
    // - id optionally allows events of the same name to be distinguished from
    //   each other. For example, to trace the consutruction and destruction of
    //   objects, specify the pointer as the id parameter.
    // - numArgs specifies the number of elements in argNames, argTypes, and
    //   argValues.
    // - argNames is the array of argument names. Use long-lived literal strings
    //   or specify the COPY flag.
    // - argTypes is the array of argument types:
    //   - BOOL (1): bool
    //   - UINT (2): unsigned long long
    //   - INT (3): long long
    //   - DOUBLE (4): double
    //   - POINTER (5): void*
    //   - STRING (6): char* (long-lived null-terminated char* string)
    //   - COPY_STRING (7): char* (temporary null-terminated char* string)
    // - argValues is the array of argument values. Each value is the unsigned
    //   long long member of a union of all supported types.
    // - thresholdBeginId optionally specifies the value returned by a previous
    //   call to addTraceEvent with a BEGIN phase.
    // - threshold is used on an END phase event in conjunction with the
    //   thresholdBeginId of a prior BEGIN event. The threshold is the minimum
    //   number of microseconds that must have passed since the BEGIN event. If
    //   less than threshold microseconds has passed, the BEGIN/END pair is
    //   dropped.
    // - flags can be 0 or one or more of the following, ORed together:
    //   - COPY (0x1): treat all strings (name, argNames and argValues of type
    //     string) as temporary so that they will be copied by addTraceEvent.
    //   - HAS_ID (0x2): use the id argument to uniquely identify the event for
    //     matching with other events of the same name.
    //   - MANGLE_ID (0x4): specify this flag if the id parameter is the value
    //     of a pointer.
    virtual Platform::TraceEventHandle addTraceEvent(
        char phase,
        const unsigned char* categoryEnabledFlag,
        const char* name,
        unsigned long long id,
        int numArgs,
        const char** argNames,
        const unsigned char* argTypes,
        const unsigned long long* argValues,
        unsigned char flags);

    // Set the duration field of a COMPLETE trace event.
    virtual void updateTraceEventDuration(const unsigned char* categoryEnabledFlag, const char* name, TraceEventHandle handle);

    // Callbacks for reporting histogram data.
    // CustomCounts histogram has exponential bucket sizes, so that min=1, max=1000000, bucketCount=50 would do.
    virtual void histogramCustomCounts(const char* name, int sample, int min, int max, int bucketCount);
    // Enumeration histogram buckets are linear, boundaryValue should be larger than any possible sample value.
    virtual void histogramEnumeration(const char* name, int sample, int boundaryValue);
    // Unlike enumeration histograms, sparse histograms only allocate memory for non-empty buckets.
    virtual void histogramSparse(const char* name, int sample);


    // GPU ----------------------------------------------------------------
    //
    // May return null if GPU is not supported.
    // Returns newly allocated and initialized offscreen WebGraphicsContext3D instance.
    virtual WebGraphicsContext3D* createOffscreenGraphicsContext3D(const WebGraphicsContext3D::Attributes&) ;

    // Returns a newly allocated and initialized offscreen context provider. The provider may return a null
    // graphics context if GPU is not supported.
    virtual WebGraphicsContext3DProvider* createSharedOffscreenGraphicsContext3DProvider() ;

    // Returns true if the platform is capable of producing an offscreen context suitable for accelerating 2d canvas.
    // This will return false if the platform cannot promise that contexts will be preserved across operations like
    // locking the screen or if the platform cannot provide a context with suitable performance characteristics.
    //
    // This value must be checked again after a context loss event as the platform's capabilities may have changed.
    virtual bool canAccelerate2dCanvas();

    virtual bool isThreadedCompositingEnabled();

    virtual WebCompositorSupport* compositorSupport() ;

    virtual WebFlingAnimator* createFlingAnimator() ;

    // Creates a new fling animation curve instance for device |deviceSource|
    // with |velocity| and already scrolled |cumulativeScroll| pixels.
    virtual WebGestureCurve* createFlingAnimationCurve(int deviceSource, const WebFloatPoint& velocity, const WebSize& cumulativeScroll) ;


    // WebRTC ----------------------------------------------------------

    // Creates an WebRTCPeerConnectionHandler for RTCPeerConnection.
    // May return null if WebRTC functionality is not avaliable or out of resources.
    virtual WebRTCPeerConnectionHandler* createRTCPeerConnectionHandler(WebRTCPeerConnectionHandlerClient*) ;

    // May return null if WebRTC functionality is not avaliable or out of resources.
    virtual WebMediaStreamCenter* createMediaStreamCenter(WebMediaStreamCenterClient*) ;


    // WebWorker ----------------------------------------------------------

    virtual void didStartWorkerRunLoop(const WebWorkerRunLoop&);
    virtual void didStopWorkerRunLoop(const WebWorkerRunLoop&);


    // WebCrypto ----------------------------------------------------------

    virtual WebCrypto* crypto() ;


    // Device Motion / Orientation ----------------------------------------

    // Sets a Listener to listen for device motion data updates.
    // If null, the platform stops providing device motion data to the current listener.
    virtual void setDeviceMotionListener(blink::WebDeviceMotionListener*) ;

    // Sets a Listener to listen for device orientation data updates.
    // If null, the platform stops proving device orientation data to the current listener.
    virtual void setDeviceOrientationListener(blink::WebDeviceOrientationListener*) ;


    // Quota -----------------------------------------------------------

    // Queries the storage partition's storage usage and quota information.
    // WebStorageQuotaCallbacks::didQueryStorageUsageAndQuota will be called
    // with the current usage and quota information for the partition. When
    // an error occurs WebStorageQuotaCallbacks::didFail is called with an
    // error code.
    // The callbacks object is deleted when the callback method is called
    // and does not need to be (and should not be) deleted manually.
    virtual void queryStorageUsageAndQuota(
        const WebURL& storagePartition,
        WebStorageQuotaType,
        WebStorageQuotaCallbacks*) ;


    // WebDatabase --------------------------------------------------------

    virtual WebDatabaseObserver* databaseObserver() ;

private:
    WebThemeEngineImpl m_themeEngine;

    base::MessageLoop* main_loop_;
    base::OneShotTimer<PlatformImpl> shared_timer_;
    void(*shared_timer_func_)();
    double shared_timer_fire_time_;
    bool shared_timer_fire_time_was_set_while_suspended_;
    int shared_timer_suspended_;  // counter
};


#endif // WebTestThemeEngineWin_h
