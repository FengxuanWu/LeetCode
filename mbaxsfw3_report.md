The phase 3 function is a separate process that completes when it has no further work to do. The phase 3 Routing function is blocked from running while the Phase 2 decision function is in process.

All routes in the Loc-RIB are processed in to <b>Adj-RIBs-Out</b> according to configured policy. This policy MAY exclude a route in the Loc-RIB from being installed in a particular <b>Adj-RIB-Out</b>. 

A route SHALL NOT be installed in the <b>Adj-RIB-Out</b> unless the destination, and <i><b>NEXT_HOP</b></i> described by this route, may be forwarded appropriately by the Routing Table. 

If in Loc-RIB is excluded from a particular <b>Adj-RIB-Out</b>, the previously advertised route in that <b>Adj-RIB-Out</b> MUST be withdrawn from service by means of an <i><b>UPDATE</b></i> message.

Route aggregation and information reduction techniques may optionally be applied.

When the updating of the <b>Adj-RIBs-Out</b> and the Routing Table is complete, the local BGP speaker runs the Update-Send process.

#### Overlapping Routes
A BGP speaker may transmit routes with overlapping Network Layer Reachability Information(NLRI) to another BGP speaker. <mark>NLRI overlap occurs when a set of destinations are identified in non-matching multiple routes.</mark> Because BGP encodes NLRI using IP prefixes, overlap will always exhibit subset relationships. <b>A route describing a smaller set of destinations (a longer prefix) is said to be more specific than a route describing a larger set of destinations (a shorter prefix), vice versa</b>.

The precedence relationship effectively decomposes less specific routes into 2 parts:
 <ul>
    <li> a set of destinations described only by the less specific route, and </li>
    <li> a set of destinations described by the overlap of the overlap of the less specific and the more specific routes </li>
</ul>

The set of destinations described by the overlap represents a portion of the less specific route that is feasible, but is not currently in use. If a more specific route is later withdrawn, the set of destinations described by the overlap will still be reachable using the less specific route. 

If a BGP speaker receives overlapping routes, the Decision Process MUST consider both routes based on the configured acceptance policy. If both a less and a more specific route are accepted, then the Decision Process MUST install, in Loc-RIB, either both the less and the more specific routes or aggregate the 2 routes and install, in Loc-RIB, the aggregated route, provided that both routes have the same value of the <i><b>NEXT_HOP</b></i> attribute.

If a BGP speaker chooses to aggregate, then it SHOULD either include all ASes used to form the aggregate in an <i><b>AS_SET</i></b>, or add the <i><b>ATOMIC_AGGREGATE</i></b> attribute to the route. This attribute is now primarily informational. With the elimination of router and host implementations that do not support classless routing, there is no longer a need to de-aggregated. In particular, a route that carries the <i><b>ATOMIC_AGGREGATE</i></b> attribute MUST NOT be de-aggregated. That is, the NLRI of this route cannot be more specific. Forwarding along such a route does not guarantee that IP packets will actually traverse only ASes listed in the <i><b>AS_PATH</i></b> attribute of the route.

### Update-Send process
The Update-Send process is responsible for advertising <i><b>UPDATE</i></b> messages to all peers. For example, it <b>distributes the routes</b> chosen by the Decision Process to other BGP speakers, which may be located in either the <b>same AS</b> or a <b>neighboring AS</b>.

When a BGP speaker receives an <i><b>UPDATE</i></b> message from an internal peer, the receiving BGP speaker SHALL NOT re-distribute the routing information contained in that <i><b>UPDATE</i></b> message to other internal peers(unless the speaker acts as a BGP Route Reflector).

As part of Phase 3 of the route selection process, the BGP speaker has updated its <b>Adf-RIBs-Out</b>. All newly installed routes and all newly feasible routes for which there is no replacement route SHALL be advertised to its peers by means of an <i><b>UPDATE</i></b> message.

A BGP speaker SHOULD NOT advertise a given feasible BGP route from its <b>Adj-RIB-Out</b> if it would produce an <i><b>UPDATE</i></b> message containing the same BGP route as was previously advertised.

Any routes in the Loc-RIB marked as unfeasible SHALL be removed. Changes to the reachable destinations within its own AS SHALL also be advertised in an <i><b>UPDATE</i></b> message.

If, due to the limits on the maximum size of an <i><b>UPDATE</i></b> message, a single route doesn't fit into the message, the BGP speaker MUST not advertise the route to its peers and MAY choose to log an error locally.

#### Controlling Routing Traffic Overhead
The BGP protocol <b>constrains the amount of routing traffic</b> (that is, <i><b>UPDATE</i></b> messages), in order to <b>limit</b> both the </b>link bandwidth</b> needed to advertise <i><b>UPDATE</i></b> messages and the <b>processing power</b> needed by the Decision Process to digest the information contained in the <i><b>UPDATE</i></b> messages.

<ul>
    <li> 
        <div> <b>Frequency of Route Advertisement</b> </div>
        <div>
            <mark><b>MinRouteAdvertisementIntervalTimer</b></mark> determines the minimum amount of time that must elapse between an advertisement and/or withdrawal of routes to a particular destination by a BGP speaker to a peer. This rate limiting procedure applies on a per-destination basis, although the value of it is set on a per BGP peer basis. 2 <b><i>UPDATE</b></i> messages sent by a BGP speaker to a peer that advertise feasible routes and/or withdrawal of unfeasible routes to some common set of destinations MUST be separated by at least <b>MinRouteAdvertisementIntervalTimer</b>. This can only be achieved by keeping a separate timer for each common set of destinations. This would be unwarranted overhead. Any techniques that ensures that the interval between 2 <i><b>UPDATE</i></b> messages sent from a BGP speaker to a peer that advertise feasible routes and/or withdrawal of unfeasible routes to some common set of destinations will be at least <b>MinRouteAdvertisementIntervalTimer</b>, and will also ensure that a constant upper bound on the interval is acceptable. Since fast convergence is needed within an AS
            <ul>
                <li> the <b>MinRouteAdvertisementIntervalTimer</b> used for interval peers SHOULD be shorter than the <b>MinRouteAdvertisementIntervalTimer</b> used for external peers. or, </li>
                <li> the procedure describe in this section SHOULD NOT apply to routes sent to internal peers.
            </ul>
            This procedure does not limit the rate of route selection, but only the rate of route advertisement. If new routes are selected multiple times while awaiting the expiration of <b>MinRouteAdvertisementIntervalTimer</b>, the last route selected SHALL be advertised at the end of <b>MinRouteAdvertisementIntervalTimer</b>.
        </div>
    </li>
    <li>
        <div> <b>Frequency of Route Origination</b> </div>
        <div>
            The parameter <b><mark>MinASOriginationIntervalTimer</mark></b> determines the minimum amount of time that must elapse between successive advertisements of <i><b>UPDATE</i></b> messages that report changes within the advertising BGP speaker's own AS.
        </div>
    </li>
</ul>

#### Efficient Organization of Routing Information
Having selected the routing information it will advertise, a BGP speaker may avail itself of several methods to organize this information in an efficient manner.

<table>
    <tr> 
        <td> Information Reduction </td>
        <td> Information reduction may imply a reduction in granularity of policy control - after information is collapsed, the same policies will apply to all destinations and paths in equivalence classes. </br>
        The Decision Process may optionally reduce the amount of information that it will place in the <b>Adj-RIBs-Out</b> by any of the following method:
        <ul>
            <li> 
                Network Layer Reachability Information (NLRI) </br>
                Destination IP address can be represent as IP address prefixes. In cases where there is a correspondence between the address structure and the systems under control of an AS administrator, it will be possible to reduce the size of the NLRI carried in the <b><i>UPDATE</i></b> messages.
            </li>
            <li>
                <b><i>AS_PATHs</b></i>:</br>
                <b><i>AS_SETs</b></i> are used in the route aggregation algorithm. They reduce the size of the <b><i>AS_PATH</b></i> information by listing each AS number only once, regardless of how many times it may have appeared in multiple <b><i>AS_PATHs</b></i> that were aggregated. </br>
                An <b><i>AS_SET</b></i> implies that the destinations listed in the NLRI can be reached through paths that traverse at least some of the constituent ASes. <b><i>AS_SETs</b></i> provide sufficient information to avoid routing information looping; however, their use may prune potentially feasible paths because such paths are no longer listed individually in the form of <b><i>AS_SEQUENCE</b></i>s. In practice, this is not likely to be a problem because once an IP packet arrives at the edge of a group of ASes, the BGP speaker is likely to have more detailed path information and can distinguish individual paths from destinations.
            </li>
        </ul>
    </tr>
    <tr>
        <td> Aggregating Routing Information </td>
        <td>
            Aggregation is the process of combining the characteristics of several different routes in such a way that a single route can be advertised. Aggregation can occur as part of the Decision Process to reduce the amount of routing information that will be placed in the <b>Adj-RIBs-Out</b>. </br> Aggregation reduces the amount of information that a BGP speaker must store and exchange with other BGP speakers. Routes can be aggregated by applying the following procedure, separately, to <b>path attributes of the same type</b> and to the <b>NLRI</b>. </br>
            <ul>
                <li>
                    Routes that have different <b><i>MULTI_EXIT_DISC</i></b> attributes SHALL NOT be aggregated.
                </li>
                <li>
                    Path attributes that have different <b>type codes</b> cannot be aggregated together.
                </li>
                <li> 
                    If the aggregated route has <b><i>AS_SET</i></b> as the first element in its <b><i>AS_PATH</i></b> attribute, then the router that originates the route SHOULD NOT advertise the <b><i>MULTI_EXIT_DISC</i></b> attribute with this route.
                </li> 
            </ul>
            Path attributes of the same type code may be aggregated, according to the following rules:
            <table>
                <tr> 
                    <td>
                        <b><i>NEXT_HOP</b></i> 
                    </td>
                    <td>
                        When aggregating routes that have different <b><i>NEXT_HOP</b></i> attributes, the <b><i>NEXT_HOP</b></i> attribute of the aggregated route SHALL identify an interface on the BGP speaker that performs the aggregation.
                    </td>
                </tr>
                <tr>
                    <td>
                        <b><i>ORIGIN</b></i>
                    </td>
                    <td>
                        If at least one route among routes that are aggregated has <b><i>ORIGIN</b></i> with the value <b>INCOMPLETE</b>, then the aggregated route MUST have the <b><i>ORIGIN</b></i> with the value <b>INCOMPLETE</b>. </br>
                        Otherwise, if at least one route among routes that are aggregated has <b><i>ORIGIN</b></i> with the value <b>EGP</b>, then the aggregated route MUST have the ORIGIN attribute with the value <b>EGP</b>. In all other cases, the value of the ORIGIN attribute of the aggregated route is <b>IGP</b>.
                    </td>
                </tr>
                <tr>
                    <td> 
                        <b><i>AS_PATH</i></b> 
                    </td>
                    <td>
                        If routes to be aggregated have identical <b><i>AS_PATH</b></i> attributes, then the aggregated route has the same <b><i>AS_PATH</b></i> attribute as each individual route. </br>
                        For the purpose of aggregating <b><i>AS_PATH</b></i> attributes, we model each AS within the <b><i>AS_PATH</b></i> attribute as a tuple <b>&lt;type, value&gt;</b>, 
                        <ul>
                            <li> 
                                <b>"type"</b> identifies a type of the path segment the AS belongs to 
                            </li> 
                            <li>
                                <b>"value"</b> identifies the AS number. 
                            </li>
                        </ul>
                            If the routes to be aggregated <b><i>AS_PATH</b></i> attribute SHALL satisfy all of the following conditions: 
                        <ul>
                            <li> 
                                all tuples of type <b><i>AS_SEQUENCE</b></i> in the aggregated <b><i>AS_PATH</i></b> SHALL appear in all the <b><i>AS_PATH</i></b>s in the initial set of routes to be aggregated.
                            </li>
                            <li>
                                all tuples of type <b><i>AS_SET</i></b> in the aggregated <b><i>AS_PATH</i></b> SHALL appear in at least one of the <b><i>AS_PATH</i></b>s in the initial set.
                            </li>
                            <li>
                                for any tuple X of type <b><i>AS_SEQUENCE</b></i> in the aggregated <b><i>AS_PATH</i></b>, which precedes tuple Y in the aggregated <b><i>AS_PATH</i></b>, X precedes Y in each <b><i>AS_PATH</i></b> in the initial set, which contains Y, regardless of the type of Y.
                            </li>
                            <li>
                                No tuple of type <b><i>AS_SET</i></b> with the same value SHALL appear more than once in the aggregated <b><i>AS_PATH</i></b>.
                            </li>
                            <li>
                                Multiple tuples of type <b><i>AS_SEQUENCE</b></i> with the same value may appear in the aggregated <b><i>AS_PATH</i></b> only when adjacent to another tuple of the same type and value.
                            </li>
                        </ul>
                        An implementation may choose any algorithm that conforms to these rules. At a minimum, a conformant implementation SHALL be able to perform the following algorithm that meets all of the above conditions:
                        <ul>
                            <li>
                                determine the longest leading sequence of tuples common to all the <b><i>AS_PATH</i></b> attributes of the routes to be aggregated. Make this sequence the leading sequence of the aggregated <b><i>AS_PATH</i></b> attribute.
                            </li>
                            <li>
                                set the type of the rest of the tuples from the <b><i>AS_PATH</i></b> attributes of the routes to be aggregated to <b><i>AS_SET</i></b>, and append them to the aggregated <b><i>AS_PATH</i></b> attribute.
                            </li>
                            <li>
                                if the aggregated <b><i>AS_PATH</i></b> has more than one tuple with the same value (regardless of tuple's type), eliminate all but one such tuple by deleting tuples of the type <b><i>AS_SET</i></b> from the aggregated <b><i>AS_PATH</i></b> attribute.
                            </li>
                            <li>
                                for each pair of adjacent tuples in the aggregated <b><i>AS_PATH</i></b>, if both tuples have the same type, merge them together, as long as doing so will not cause a segment with a length greater than 255 to be generated.
                            </li>
                        </ul>
                    </td>
                </tr>
                <tr>
                    <td>
                        <i><b>ATOMIC_AGGREGATE</b></i>
                    </td>
                    <td>
                        If at least one of the routes to be aggregated has <b><i>ATOMIC_AGGREGATE</i></b> path attribute, then the aggregated route SHALL have this attribute as well.
                    </td>
                </tr>
                <tr>
                    <td>
                        <i><b>AGGREGATOR</b></i>
                    </td>
                    <td>
                        Any <b><i>AGGREGATOR</i></b> attributes from the routes to be aggregated MUST NOT be included in the aggregated rou te. The BGP speaker performing the route aggregation MAY attach a new <b><i>AGGREGATOR</i></b> attribute.
                    </td> 
                </tr>
            </table>
        </td>
    </tr>
</table>

### Route Selection Criteria
* If the local AS appears in the AS path of the new route being considered, then that new route cannot be viewed as better than any other route (provided that the speaker is configured to accept such routes). (avoid LOOP)
* In order to achieve a successful distributed operation, only routes with a likelihood of stability can be chosen. Thus, an AS SHOULD avoid using unstable routes, and it SHOULD NOT make rapid, spontaneous change to its choice route. Quantifying the terms "unstable" and "rapid" will require experience, but the principle is clear. Routes that are unstable can be "penalized".

### Originating BGP routes
A BGP speaker may originate BGP routes by injecting routing information acquired by some other means into BGP. A BGP speaker that originates BGP routes assigns the degree of preference to these routes by passing them through the Decision Process. The decision of whether to distribute non-BGP acquired routes within an AS via BGP depends on the environment within the AS and SHOULD be controlled via configuration.

## BGP Timer
<table>
    <tr>
        <td> <b>Timer Name</b> </td>
        <td> <b>State</b> </td>
        <td> <b>Suggested Value</b> </td>
    </tr>
    <tr>
        <td> <i><b>ConnectRetryTimer</b></i> </td>
        <td> <b>Mandatory</b> </td>
        <td> 120s </td>
    </tr>
    <tr>
        <td> <i><b>HoldTime</b></i> </td>
        <td> <b>Mandatory</b> </td>
        <td> 90s </td>
    </tr>
    <tr>
        <td> <i><b>HoldTimer</b></i> </td>
        <td> <b>Mandatory and must configurable on a per-peer basis.</b> </td>
        <td> 4min </td>
    </tr>
    <tr>
        <td> <i><b>KeepaliveTime</b></i> </td>
        <td> <b>Mandatory</b> </td>
        <td> 1/3 HoldTime</b> </td>
    </tr>
    <tr>
        <td> <i><b>MinASOriginationIntervalTimer</b></i> </td>
        <td> <b>Mandatory</b> </td>
        <td> 15s </td>
    </tr>
    <tr>
        <td> <i><b>MinRouteAdvertisementIntervalTimer (EBGP)</b></i> </td>
        <td> <b>Mandatory</b> </td>
        <td> 30s </td>
    </tr>
    <tr>
        <td> <i><b>MinRouteAdvertisementIntervalTimer (IBGP)</b></i> </td>
        <td> <b>Mandatory</b> </td>
        <td> 5s </td>
    </tr>
</table>

Jitter SHOULD be applied to the timers associated with MinASOriginationIntervalTimer, and ConnectRetryTimer. Jitter need not to be configured on a per-peer basis. The suggested default amount of jitter SHALL be determined by $base*rand()$, which is uniformly distributed in the range from 0.75 - 1.0. A new random value SHOULD be picked each time the timer is set. The range of the jitter's random value MAY be configurable.